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
  if(Serial1.available() > 0){
    /* Read the coordinate string from the GPS */
    char character = Serial1.read();
    
    /* Check for the end of the coordinate */
    if(character == '\n'){
      /* The beginning of the GPS coordinates starts with $GPRMC */
      if(coordinates.startsWith("$GPRMC")){
        char coords[128];
        char *coordsPtr = coords;
        char *tokens;
        int direct;

        /* Place coordinates into char array point to separate into tokens */
        coordinates.toCharArray(coords, coordinates.length());
        /* Break NMEA into coordinate tokens */
        tokens = strtok_r(coordsPtr, ",", &coordsPtr);
        while(tokens != NULL){
          /* Convert NMEA into Degrees, mins, seconds */
          if(direct == 3 || direct == 5){
            int degreeInt;
            int degree;
            int minutes;
            int seconds;
            String compass;
          
            degreeInt = atoi(tokens);
            degree = ((int)degreeInt) / 100;
            minutes = degreeInt - (degree * 100);
            seconds = (float) (atof(tokens) - (float)degreeInt) * 60.0;
            
            if(direct == 3){
              compass = " N";
            } else if(direct == 5){
              compass = " W";
            }
            char secondsBuffer[6];
            char location[128];
            
            dtostrf(seconds, 6, 3, secondsBuffer);
            sprintf(location, "%02d\xB0 %0sd' %s", degree, minutes, secondsBuffer);
            Serial.println(location + compass);
          }
          direct++;
        }
        /* Insert a blank line for formatting */
        Serial.println();
      }
      /* Clear the coordinates for a new string */
        coordinates = "";
    } else{
      /* If it's not the end of the coordinates, add to coordinates string until complete */
      coordinates += character;
    }
  }
}

// Arduino IDE libraries do not include dtostrf()
char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
  char format[20];
  sprintf(format, "%%%d.%df", width, prec);
  sprintf(sout, format, val);
  return sout;
}
