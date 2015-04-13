//#include <Wire.h>                 //I2C library
int led=13;
void setup()
{
  Serial.begin(9600);
  Serial.flush();
  pinMode(led,OUTPUT);
  delay(500);
  quickFlash();
  delay(500);
  // digitalWrite (13, HIGH);      //turn on debugging LED
}

void loop (){

  int i=0;
  char buff[100];
  String data;
  boolean reading = false;
  if(Serial.available()){
     delay(100);
     while( Serial.available() && i< 99) {
        buff[i++] = Serial.read();
     }
     buff[i++]='\0';
  }

  if(i>0)
     data = String(buff);
  //flashNum(data.length());
  if(data.startsWith(":"))  {
    quickFlash();
    int byteCount=data.substring(1,3).toInt();
    String offset=data.substring(3,6);
    String recordType=data.substring(6,8);
    String dataRec=data.substring(8,8+(byteCount*2));
    char dataBytes[2*byteCount];
    dataRec.toCharArray(dataBytes,dataRec.length());
    Serial.print("Bytes: ");
    Serial.println(byteCount);
    Serial.print("Offset: ");
    Serial.println(offset);
    Serial.print("Rectype: ");
    Serial.println(recordType);
    Serial.print("Datarec: ");
    Serial.println(dataRec);
    for(int i=0;i<byteCount*2;i+=2)  {
      Serial.print(dataBytes[i]);
      Serial.println(dataBytes[i+1]);
      Serial.print((int)strtol(dataBytes,NULL,8));
      Serial.print((int)strtol(dataBytes,NULL,8));
      //Serial.print(hextrans(dataBytes));
      //Serial.println(hextrans(dataBytes+1));
    }
  }
}
/*
int hextrans(char b)  {
  return (int) strtol( &b, NULL, 8);
}
*/


/*

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}

*/
void quickFlash()  {
  digitalWrite(led, HIGH);
  delay(30);
  digitalWrite(led, LOW);
  delay(30);
  digitalWrite(led, HIGH);
  delay(30);
  digitalWrite(led, LOW);
  delay(30);
  digitalWrite(led, HIGH);
  delay(30);
  digitalWrite(led, LOW);
}

void oneFlash()  {
  digitalWrite(led, HIGH);
  delay(30);
  digitalWrite(led, LOW);
}

void flashNum(int num)  {
  for(int i=0;i<num;i++)  {
    digitalWrite(led,HIGH);
    delay(75);
    digitalWrite(led,LOW);
    delay(100);
  }
}
