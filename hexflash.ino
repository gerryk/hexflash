#include <Wire.h>                 //I2C library

int led=13;
void setup()
{
  Serial.begin(9600);
  Serial.flush();
  pinMode(led,OUTPUT);
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
  if(data.startsWith(":"))  {
    byte decByte;
    char tmp[3];
    tmp[2] = '\0';
    quickFlash();
    data.substring(1,3).toChar(buff, 2);
    int byteCount=(int)strtol( buff, NULL, 16);
    String offset=data.substring(3,6);
    String recordType=data.substring(6,8);

    Serial.print("Bytes: ");
    Serial.println(byteCount);
    Serial.print("Offset: ");
    Serial.println(offset);
    Serial.print("Rectype: ");
    Serial.println(recordType);
    Serial.print("Datarec: ");
    Serial.println(dataRec);
    
    for(int i=0;i<byteCount*2;i+=2)  {
      quickFlash();
      Serial.print(dataBytes[i]);
      Serial.println(dataBytes[i+1]);
      tmp[0] = dataBytes[i];
      tmp[1] = dataBytes[i+1];
      decByte=strtol(tmp,0,16);
      Serial.println(decByte);  
    }
  }
}


void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}


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
