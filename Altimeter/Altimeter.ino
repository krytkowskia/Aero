/************************************
*  Aero Team
*  Altimeter, Barometric Pressure, Temperature
*  10-27-2014
*
*  Pull up resistors are located on pins 20 and 21
*
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
  
  /* Convert altitude, meters to feet */
  float feet = BMP.pressureToAltitude(SENSORS_PRESSURE_SEALEVELHPA, event.pressure) * 3.28084;
  Serial.print("Altitude:    ");
  Serial.print(feet);
  Serial.println(" ft");
  
  float temperature;
  BMP.getTemperature(&temperature);
  /* Convert temperature, celsius to fahrenheit */
  float fahrenheit = temperature * 33.8;
  Serial.print("Temperature: ");
  Serial.print(fahrenheit);
  Serial.print(" F");
  
  /* Standard Atmospheric Pressure = 1,013.25 hPA */
  Serial.print("Pressure:    ");
  Serial.print(event.pressure);
  Serial.println(" hPa\n");
}
