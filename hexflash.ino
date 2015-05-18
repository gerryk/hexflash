#include <Wire.h>                 //I2C library

int led=13;
String data;
int ledstate = HIGH;
char buff[50];
char ch;

void setup()
{
  Serial.begin(9600);
  Wire.begin();  
  //Serial.flush();
  pinMode(led,OUTPUT);
  digitalWrite(led, LOW);
  quickFlash();
}

void loop ()  {
  while (!Serial.available()); //wait for user input
  //Serial.println(Serial.available());
  while (Serial.available())  {
     //Serial.println("Reading...");
     data = Serial.readStringUntil('\n');
     if(data.startsWith(":"))  {
       ledstate = ledstate==HIGH?LOW:HIGH;
       digitalWrite(led, ledstate);
       byte decByte;
       char tmp[3];
       tmp[2] = '\0';
       data.substring(1,3).toCharArray(buff, 3);
       int byteCount=(int)strtol(buff, NULL, 16);
       String offset=data.substring(3,7);
       data.substring(3,5).toCharArray(buff,3);
       unsigned int msbOffset=(int)strtol(buff, NULL, 16);
       data.substring(5,7).toCharArray(buff,3);
       unsigned int lsbOffset=(int)strtol(buff, NULL, 16);
       String recordType=data.substring(7,9);
       data.substring(9,10+2*byteCount).toCharArray(buff,1+2*byteCount);  
       data = ""; // Clear recieved buffer
       if(recordType=="00")  {
         for(unsigned int i=0;i<byteCount*2;i+=2)  {
           tmp[0] = buff[i];
           tmp[1] = buff[i+1];
           decByte=strtol(tmp,0,16);
           writeEEPROM(0x50,msbOffset*256+lsbOffset+(i/2),decByte);
         }
         Serial.println("OK");
       } else if(recordType=="01")  {     // EOF
       } else if(recordType=="02")  {     // ES Address
       } else if(recordType=="03")  {     // SS Address
       } else if(recordType=="04")  {     // Ext. Linear Address  (32 bit addressing - page offset)
       } else if(recordType=="05")  {     // Start Linear Address (32 bit addressing EIP register)
       }
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
  //delay(5);
  oneFlash();
}
 
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress,1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}

void quickFlash()  {
  digitalWrite(led, HIGH);
  delay(10);
  digitalWrite(led, LOW);
  delay(10);
  digitalWrite(led, HIGH);
  delay(10);
  digitalWrite(led, LOW);
  delay(10);
  digitalWrite(led, HIGH);
  delay(10);
  digitalWrite(led, LOW);
}

void oneFlash()  {
  digitalWrite(led, HIGH);
  delay(5);
  digitalWrite(led, LOW);
  delay(5);
}

