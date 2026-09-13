#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Parking Sensor"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char ssid[] = "YOUR_WIFI";
char pass[] = "YOUR_PASSWORD";

#define TRIG_PIN 5
#define ECHO_PIN 18

#define LED_GREEN 25
#define LED_YELLOW 26
#define LED_RED 27
#define BUZZER 14

LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

float distanceCm;

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  return duration * 0.0343 / 2;
}

void sendData() {
  distanceCm = readDistance();

  String status;

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(BUZZER, LOW);

  if (distanceCm > 30) {
    status = "DI LUAR JANGKAUAN";
    digitalWrite(LED_GREEN, HIGH);
  }
  else if (distanceCm >= 25) {
    status = "AMAN";
    digitalWrite(LED_GREEN, HIGH);
  }
  else if (distanceCm >= 15) {
    status = "WASPADA";
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(BUZZER, HIGH);
  }
  else if (distanceCm >= 0) {
    status = "BAHAYA";
    digitalWrite(LED_RED, HIGH);
    digitalWrite(BUZZER, HIGH);
  }
  else {
    status = "SENSOR ERROR";
  }

  lcd.clear();
  lcd.setCursor(0, 0);

  if (distanceCm >= 0) {
    lcd.print("Jarak: ");
    lcd.print(distanceCm, 1);
    lcd.print(" cm");
  } else {
    lcd.print("Sensor Error");
  }

  lcd.setCursor(0, 1);
  lcd.print(status);

  Blynk.virtualWrite(V0, distanceCm);
  Blynk.virtualWrite(V1, status);
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Parking Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
