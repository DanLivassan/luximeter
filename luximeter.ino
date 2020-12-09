#include <Wire.h> 
#include <BH1750.h> 
#include <SoftwareSerial.h>
#include <TinyGPS.h>
 
TinyGPS gps;
 
#define GPS_RX 10
#define GPS_TX 11
#define GPS_Serial_Baud 9600

// The serial connection to the GPS device
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);

//Lightmeter
BH1750 lightMeter; 
 
void setup(){
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  gpsSerial.begin(GPS_Serial_Baud);
}
 
void loop() {
  
  Serial.println(getData());
}


float getLux(){
  return lightMeter.readLightLevel();
}

String getData(){
  bool newData = false;
  unsigned long chars;
  
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (gpsSerial.available())
    {
      char c = gpsSerial.read();
       
      if (gps.encode(c))
        newData = true;
    }
  }
  if (newData)
  {
    float flat, flon;
    String lat, lon, lux;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    lux = String(getLux());
    
    lat = String(flat,6);
    lon = String(flon,6);
    return lat+","+lon+","+lux;
  }
}
