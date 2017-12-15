#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(7,8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo servo4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  servo4.attach(6);
}

void loop() {
  int a[3];
    
  radio.startListening();
  if ( radio.available()) 
    {
       while (radio.available()) 
        { 
         
           
              radio.read(&a[3], sizeof(a[3]));
              delay(100);
              Serial.print(3);
              Serial.print(" : ");
              Serial.print(a[3]);
              Serial.println(" ");
           
      
        }
    
  
  
    }
  switch (a[3]) 
   {
    case 9  :  servo4.write(0); break;
    case 10 :  servo4.write(90);break;
    case 11 :  servo4.write(180);break;
   
   }

}
