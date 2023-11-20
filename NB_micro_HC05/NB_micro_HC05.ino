#include<SoftwareSerial.h>

/* Create object named bt of the class SoftwareSerial */ 
// WORKS WITH UNO
// SoftwareSerial bt(2,3); /* (Rx,Tx) */ 

void setup(){
  // WORKS WITH UNO
  // bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600);  /* Define baud rate for serial communication */
  Serial1.begin(9600);
}

void loop(){
    if (Serial1.available()) /* If data is available on serial port */
    {
      while(Serial1.available()) {
        Serial.write(Serial1.read());      /* Print character received on to the serial monitor */
      }
    }

    if (Serial.available()) {
      Serial1.write(Serial.read());
    }

    /**if (Serial1.availableForWrite())
    {
      Serial1.write("Hello master!\n");
      delay(1000);
    }**/
}