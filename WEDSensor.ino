#include <Wire.h>
#include <math.h>
#include <SD.h>
#include <SPI.h>

const int MPU=0x68; 
int16_t X,Y,Z;

const int chipSelect = 10;
int transmitPin = 8;
int measurment = 0;

void setup() {
  Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);
  
  SD.begin(chipSelect);
 
  pinMode(transmitPin, OUTPUT);
}

void loop() {
  if(findIntensity()>4.17){
    digitalWrite(transmitPin,HIGH);
  }
  else{
    digitalWrite(transmitPin,LOW);
  }

  printDataToFile(findIntensity());

  delay(500);
}

float findIntensity(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  X=Wire.read()<<8|Wire.read();    
  Y=Wire.read()<<8|Wire.read();  
  Z=Wire.read()<<8|Wire.read();

  float pga = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
  float richterIntensity = log10(pga);

  Serial.print(richterIntensity);
  Serial.print("\n");

  return richterIntensity;
}

void printDataToFile(float intensity){
  File dataFile = SD.open("data.txt", FILE_WRITE);

  dataFile.print("measurement ");
  dataFile.print(measurment);
  dataFile.print(":");
  dataFile.println(intensity);
  dataFile.close();

  measurment++;
}
