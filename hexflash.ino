// #define DEBUG 1

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
    data.substring(1,3).toCharArray(buff, 3);
    int byteCount=(int)strtol(buff, NULL, 16);
    String offset=data.substring(3,7);
    data.substring(3,5).toCharArray(buff,3);
    int msbOffset=(int)strtol(buff, NULL, 16);
    data.substring(5,7).toCharArray(buff,3);
    int lsbOffset=(int)strtol(buff, NULL, 16);
    String recordType=data.substring(7,9);
    data.substring(9,10+2*byteCount).toCharArray(buff,1+2*byteCount);  
    #ifdef DEBUG
    Serial.print("Bytes: ");
    Serial.println(byteCount);
    Serial.print("HexOffset: ");
    Serial.println(offset);
    Serial.print("DecOffset: ");
    Serial.println(msbOffset*256+lsbOffset);
    Serial.print("Rectype: ");
    Serial.println(recordType);
    Serial.print("Datarec: ");
    Serial.println(buff);
    #endif
    if(recordType=="00")  {
      for(int i=0;i<byteCount*2;i+=2)  {
        #ifdef DEBUG
        quickFlash();
        Serial.print("Byte: ");
        Serial.print(i/2);      
        Serial.print(" : ");
        Serial.print(buff[i]);
        Serial.print(buff[i+1]);
        #endif
        tmp[0] = buff[i];
        tmp[1] = buff[i+1];
        decByte=strtol(tmp,0,16);
        #ifdef DEBUG
        Serial.print(" Offset: ");
        Serial.print(msbOffset*256+lsbOffset+i/2);      
        Serial.print(" :: ");
        Serial.println(decByte);  
        #endif
        #ifndef DEBUG
        writeEEPROM(0x50,msbOffset*256+lsbOffset+i,decByte);
        #endif
      }
      for(int j=0;j<16;j++)  {
        Serial.println("Reading Bytes");
        Serial.println(i2c_eeprom_read_byte(0x50,msbOffset*256+lsbOffset+j));
      }
    }
  }
}


byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress ) {
    byte rdata = 0xFF;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceaddress,1);
    if (Wire.available()) rdata = Wire.read();
    return rdata;
  }

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
  oneFlash();
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
