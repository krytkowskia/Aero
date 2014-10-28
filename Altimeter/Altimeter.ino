/************************************
*  Aero Team
*  Altimeter, Barometric Pressure, Temperature
*  10-27-2014
*************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified BMP = Adafruit_BMP085_Unified(10085);

void setup(void){
  /* Open serial connection for altimeter */
  Serial.begin(9600);
}

void loop(void){
  sensors_event_t event;
  BMP.getEvent(&event);
  
  Serial.print("Altitude:    ");
  Serial.print(BMP.pressureToAltitude(SENSORS_PRESSURE_SEALEVELHPA, event.pressure));
  Serial.println(" m");
  
  float temperature;
  BMP.getTemperature(&temperature);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C");
  
  Serial.print("Pressure:    ");
  Serial.print(event.pressure);
  Serial.println(" hPa\n");
}
