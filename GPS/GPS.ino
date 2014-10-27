/*************************************
*  Aero Team
*  GPS
*  10-27-2014
**************************************/

#include<string.h>

String coordinates;

void setup(){
  /* Serial is for outputting to the arduino serial monitor */
  Serial.begin(9600);
  /* Serial1 is for connecting to the adafruit GPS */
  Serial1.begin(9600); 
}

void loop(){
  /* Check if the GPS is spitting out bytes for the Due to read */
  if(Serial1.avaiable() > 0){
    /* Read the coordinate string from the GPS */
    char character = Serial1.read();
    
    /* Check for the end of the coordinate */
    if(character == '\n'){
      /* Check for the beginning of a coordinates */
      /* Calculate the coordinates into degrees, mins, seconds */
    } else{
      /* If it's not the end of the coordinates, add to coordinates string until complete */
      coordinates += character;
    }
  }
}
