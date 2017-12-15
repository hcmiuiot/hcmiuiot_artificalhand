#include<Wire.h>
#define accel_module (0x1D)
  byte values[2] ;
char output[512];
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
void setup() {
  Wire.begin();
Serial.begin(9600);
Wire.beginTransmission(accel_module);
Wire.write(0x2D);
Wire.write(0);
Wire.endTransmission();
Wire.beginTransmission(accel_module);
Wire.write(0x2D);
Wire.write(16);
Wire.endTransmission();
Wire.beginTransmission(accel_module);
Wire.write(0x2D);
Wire.write(8);  
Wire.endTransmission();
radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
  radio.setPALevel(RF24_PA_MIN);

}

void loop() {
  int xregister = 0x32;
int x;
int a[3];
int t[3];

Wire.beginTransmission(accel_module);
Wire.write(xregister);
Wire.endTransmission();

Wire.beginTransmission(accel_module);
Wire.requestFrom(accel_module, 2);

int i = 0;
while(Wire.available()){
values[i] = Wire.read();
i++;
}

Wire.endTransmission();
x = (((int)values[1]) << 8) | values[0] ;
a[3]=x;
 if (a[3]<100) t[3]=9; 
    else 
       if ((a[3]>100) && (a[3]<200)) t[3]=10; 
          else 
             if (a[3]>200) t[3]=11;
sprintf(output, "%d ", x); 
Serial.print(output); 
Serial.write(10); 

  Serial.print(3);
  Serial.print(" : ");
  Serial.print(t[3]);
  Serial.println(" ");
  radio.write(&t[3],sizeof(t[3]));
  delay(100);

}
