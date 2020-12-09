#include <Wire.h> 
#include <BH1750.h> 
 
BH1750 lightMeter; 
 
void setup(){
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
}
 
void loop() {
  
  Serial.print(getLux(lightMeter)); 
  delay(1000); 
}


float getLux(BH1750 lightMeter){
  return lightMeter.readLightLevel();
}
