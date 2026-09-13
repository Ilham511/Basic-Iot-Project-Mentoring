#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;
HardwareSerial GPSserial(1);

#define GPS_RX 16
#define GPS_TX 17

void setup() {
  Serial.begin(115200);

  GPSserial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  Serial.println("GPS Vehicle Monitoring");
}

void loop() {
  while (GPSserial.available() > 0) {
    gps.encode(GPSserial.read());
  }

  if (gps.location.isUpdated()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);

    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);

    Serial.print("Speed: ");
    Serial.print(gps.speed.kmph());
    Serial.println(" km/h");

    Serial.println("--------------------");
  }
}
