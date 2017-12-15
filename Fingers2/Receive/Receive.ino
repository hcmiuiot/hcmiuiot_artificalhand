#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(7,8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo servo2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  servo2.attach(4);
}

void loop() {
  int a[1];
    
  radio.startListening();
  if ( radio.available()) 
    {
       while (radio.available()) 
        { 
         
           
              radio.read(&a[1], sizeof(a[1]));
              delay(100);
              Serial.print(1);
              Serial.print(" : ");
              Serial.print(a[1]);
              Serial.println(" ");
           
      
        }
    
  
  
    }
  switch (a[1]) 
   {
    case 3  :  servo2.write(180); break;
    case 4  :  servo2.write(90);break;
    case 5  :  servo2.write(0);break;
   
   }

}
