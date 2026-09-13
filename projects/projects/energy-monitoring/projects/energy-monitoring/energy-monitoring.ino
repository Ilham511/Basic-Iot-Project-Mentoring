#include <PZEM004Tv30.h>
#include <HardwareSerial.h>

#define PZEM_RX 16
#define PZEM_TX 17

HardwareSerial pzemSerial(2);
PZEM004Tv30 pzem(pzemSerial, PZEM_RX, PZEM_TX);

void setup() {
  Serial.begin(115200);
  pzemSerial.begin(9600, SERIAL_8N1, PZEM_RX, PZEM_TX);

  Serial.println("AC Electrical Energy Monitoring");
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();

  Serial.println("--------------------");

  Serial.print("Voltage    : ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Current    : ");
  Serial.print(current);
  Serial.println(" A");

  Serial.print("Power      : ");
  Serial.print(power);
  Serial.println(" W");

  Serial.print("Energy     : ");
  Serial.print(energy);
  Serial.println(" kWh");

  Serial.print("Frequency  : ");
  Serial.print(frequency);
  Serial.println(" Hz");

  Serial.print("Power Factor: ");
  Serial.println(pf);

  delay(2000);
}
