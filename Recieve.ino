  /*
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SoftwareSerial.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
#define RxD 10  
#define TxD 11  
SoftwareSerial BTSerie(RxD,TxD);


boolean buttonState = 0;
void setup() 
{
  servo1.attach(3);
  servo2.attach(4);
  servo3.attach(5);
  servo4.attach(6);
  servo5.attach(7);
  
  BTSerie.begin(9600); 
  Serial.begin(9600);
  
}

void loop() 
{
int a[4];
    
  
  if ( BTSerie.available()>0) 
    {
       
         for (int i=0;i<4;i++)
           {
              
              a[i] = BTSerie.read(); // Reads the data from the serial port
              Serial.print(i);
              Serial.print(" : ");
              Serial.print(a[i]);
              delay(100);
              Serial.println(" ");
           }
      
        
    
  
  
    }
  switch (a[0]) 
   {
    case 0  :  servo1.write(180); break;
    case 1  :  servo1.write(90);break;
    case 2  :  servo1.write(0);break;
    case 3  :  servo2.write(180); break;
    case 4  :  servo2.write(90);break;
    case 5  :  servo2.write(0);break;
    case 6  :  servo3.write(0); break;
    case 7  :  servo3.write(90);break;
    case 8  :  servo3.write(180);break;
    case 9  :  servo4.write(0); break;
    case 10 :  servo4.write(90);break;
    case 11 :  servo4.write(180);break;
   
   }
  switch (a[1]) 
   { 
   
    case 1  :  servo1.write(90);break;
    case 2  :  servo1.write(0);break;
    case 3  :  servo2.write(180); break;
    case 4  :  servo2.write(90);break;
    case 5  :  servo2.write(0);break;
    case 6  :  servo3.write(0); break;
    case 7  :  servo3.write(90);break;
    case 8  :  servo3.write(180);break;
    case 9  :  servo4.write(0); break;
    case 10 :  servo4.write(90);break;
    case 11 :  servo4.write(180);break;
   }
  switch (a[2])
   {
    
    case 1  :  servo1.write(90);break;
    case 2  :  servo1.write(0);break;
    case 3  :  servo2.write(180); break;
    case 4  :  servo2.write(90);break;
    case 5  :  servo2.write(0);break;
    case 6  :  servo3.write(0); break;
    case 7  :  servo3.write(90);break;
    case 8  :  servo3.write(180);break;
    case 9  :  servo4.write(0); break;
    case 10 :  servo4.write(90);break;
    case 11 :  servo4.write(180);break;
   }
  switch(a[3])
   {
    case 1  :  servo1.write(90);break;
    case 2  :  servo1.write(0);break;
    case 3  :  servo2.write(180); break;
    case 4  :  servo2.write(90);break;
    case 5  :  servo2.write(0);break;
    case 6  :  servo3.write(0); break;
    case 7  :  servo3.write(90);break;
    case 8  :  servo3.write(180);break;
    case 9  :  servo4.write(0); break;
    case 10 :  servo4.write(90);break;
    case 11 :  servo4.write(180);break;
   }
 
   
  
 
}


