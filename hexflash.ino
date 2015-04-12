#include <Wire.h>                 //I2C library

const int MAXLINE = 256;

void setup() {
    Serial.begin(9600);
}

void loop() {
    String s(readSerialBytes());
    Serial.println(s);
    if (s == "START")  {
        int startAddress = 0;
        while (s != "END")  {
        }
    }
}

char* readSerialBytes()  {
  char data[MAXLINE];
  static boolean recvInProgress = false;
  static byte i = 0;
  boolean newData = false;
  char startMarker = ';';
  char endMarker = '\0';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    if (recvInProgress == true) {
      if (rc != endMarker) {
        data[i] = rc;
	i++;
	if (i >= MAXLINE) {
	  i = MAXLINE - 1;
	}
      }
    else {
      data[i] = '\0'; // terminate the string
      recvInProgress = false;
      i = 0;
      newData = true;
    }
  }
  else if (rc == startMarker) {
    recvInProgress = true;
  }
}
}

void writeBytes(String s)  {
    //Wire.write((int)(eeaddress & 0xFF)); // LSB
    //Wire.endTransmission();
    //Wire.requestFrom(deviceaddress,1);
    //if (Wire.available()) rdata = Wire.read();
    //return rdata;
}
