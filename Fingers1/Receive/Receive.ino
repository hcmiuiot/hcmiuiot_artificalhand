#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(7,8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo servo1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  servo1.attach(3);
}

void loop() {
  int a[0];
    
  radio.startListening();
  if ( radio.available()) 
    {
       while (radio.available()) 
        { 
         
           
              radio.read(&a[0], sizeof(a[0]));
              delay(100);
              Serial.print(0);
              Serial.print(" : ");
              Serial.print(a[0]);
              Serial.println(" ");
           
      
        }
    
  
  
    }
  switch (a[0]) 
   {
    case 0  :  servo1.write(180); break;
    case 1  :  servo1.write(90);break;
    case 2  :  servo1.write(0);break;
   
   }

}
