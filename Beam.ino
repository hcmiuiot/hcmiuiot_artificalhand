  
#define accel_module (0x1D)
byte values[2] ;
char output[512];
#define accel_module1 (0x53)
byte values1[6] ;
char output1[512];
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
MPU6050 mpu1(0x69);
#define OUTPUT_READABLE_YAWPITCHROLL
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
Quaternion q;           // [w, x, y, z]         quaternion container

VectorFloat gravity;    // [x, y, z]            gravity vector
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
bool dmpReady1 = false;  // set true if DMP init was successful
uint8_t mpuIntStatus1;   // holds actual interrupt status byte from MPU
uint8_t devStatus1;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize1;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount1;     // count of all bytes currently in FIFO
uint8_t fifoBuffer1[64]; // FIFO storage buffer
// packet structure for InvenSense teapot demo

Quaternion q1;           // [w, x, y, z]         quaternion container

VectorFloat gravity1;    // [x, y, z]            gravity vector

float ypr1[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket1[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };
void setup(){
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
Serial.begin(115200);
TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
   
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

   
    
    mpu.initialize();
    
    

    
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
    mpu1.initialize();
    
    

    // load and configure the DMP
    
    devStatus1 = mpu1.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu1.setXGyroOffset(220);
    mpu1.setYGyroOffset(76);
    mpu1.setZGyroOffset(-85);
    mpu1.setZAccelOffset(1788); // 1688 factory default for my test chip

    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
      
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    } 
    if (devStatus1 == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu1.setDMPEnabled(true);

        // enable Arduino interrupt detection
        
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu1.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
       
        dmpReady1 = true;

        // get expected DMP packet size for later comparison
        packetSize1 = mpu1.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus1);
        Serial.println(F(")"));
    }

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
  Wire.beginTransmission(accel_module1);
  Wire.write(0x2D);
  Wire.write(0);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module1);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module1);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}
volatile bool mpuInterrupt1 = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady1() {
    mpuInterrupt1 = true;
}
void loop(){
int xregister = 0x32;
int x;
if (!dmpReady) return;
if (!dmpReady1) return;
 mpuInterrupt = false;
 mpuInterrupt1 = false;
 mpuIntStatus = mpu.getIntStatus();
 mpuIntStatus1 = mpu1.getIntStatus();
  fifoCount = mpu.getFIFOCount();
  fifoCount1 = mpu1.getFIFOCount();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;
        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("r\t");
            Serial.println(ypr[2] * 180/M_PI);
        #endif

}
  if ((mpuIntStatus1 & 0x10) || fifoCount1 == 1024) {
        // reset so we can continue cleanly
        mpu1.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus1 & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount1 < packetSize1) fifoCount1 = mpu1.getFIFOCount();

        // read a packet from FIFO
        mpu1.getFIFOBytes(fifoBuffer1, packetSize1);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount1 -= packetSize1;
      

      

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("r\t");
            
            Serial.println(ypr[2] * 180/M_PI);
        #endif

         #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu1.dmpGetQuaternion(&q1, fifoBuffer1);
            mpu1.dmpGetGravity(&gravity1, &q1);
            mpu1.dmpGetYawPitchRoll(ypr1, &q1, &gravity1);
            Serial.print("r1\t");
            Serial.println(ypr1[2] * 180/M_PI);
        #endif

       Wire.beginTransmission(accel_module);
  Wire.write(xregister);
  Wire.endTransmission();

  Wire.beginTransmission(accel_module);
  Wire.requestFrom(accel_module, 2);

  int i = 0;
  while(Wire.available()){
  values[i] = Wire.read();
  i++;
  Wire.endTransmission();
  x = (((int)values[1]) << 8) | values[0];

  sprintf(output, "%d ", x); 
  Serial.print("xADXL3455:");
  Serial.print(output); 
  Serial.write(10); 
   }
  int x1register = 0x32;
  int x1;
  Wire.beginTransmission(accel_module1);
  Wire.write(x1register);
  Wire.endTransmission();

  Wire.beginTransmission(accel_module1);
  Wire.requestFrom(accel_module1, 6);

  int j = 0;
  while(Wire.available())
  {
    values1[j] = Wire.read();
    j++;
  }
  Wire.endTransmission();
  x1 = (((int)values1[1]) << 8) | values1[0];

  sprintf(output1, "%d ", x1); 
  Serial.print("ADXL3455 3 :");
  Serial.print(output1); 
  Serial.write(10); 
   
  int t[4];
  float a[4];
  a[0]=ypr[2]* 180/M_PI;
  a[1]=ypr1[2]* 180/M_PI;
  a[2]=x;
  a[3]=x1;
  if ((a[0]<0)&&(a[0]>-25)) t[0]=0; 
    else 
       if ((a[0]<-25) && (a[0]>-45)) t[0]=1; 
          else 
             if (a[0]<-45) t[0]=2;
  if (a[1]>-25) t[1]=3; 
    else 
       if ((a[1]<-25) && (a[1]>-45)) t[1]=4; 
          else 
             if (a[1]<-45) t[1]=5;
  if (a[2]<100) t[2]=6; 
    else 
       if ((a[2]>100) && (a[2]<200)) t[2]=7; 
          else 
             if (a[2]>200) t[2]=8;
  if (a[3]<100) t[3]=9; 
    else 
       if ((a[3]>100) && (a[3]<200)) t[3]=10; 
          else 
             if (a[3]>200) t[3]=11;
 for (int z=0;z<4;z++) 
  {
  radio.write(&t[z],sizeof(t[z]));
  delay(100);
  Serial.print(z);
              Serial.print(" : ");
              Serial.print(t[z]);
              Serial.println(" ");
  
  }
        
    }
  
} 
