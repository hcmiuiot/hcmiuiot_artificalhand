#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(7,8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo servo3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  servo3.attach(5);
}

void loop() {
  int a[2];
    
  radio.startListening();
  if ( radio.available()) 
    {
       while (radio.available()) 
        { 
         
           
              radio.read(&a[2], sizeof(a[2]));
              delay(100);
              Serial.print(2);
              Serial.print(" : ");
              Serial.print(a[2]);
              Serial.println(" ");
           
      
        }
    
  
  
    }
  switch (a[2]) 
   {
    case 6  :  servo3.write(-90); break;
    case 7  :  servo3.write(90);break;
    case 8  :  servo3.write(180);break;
   
   }

}
