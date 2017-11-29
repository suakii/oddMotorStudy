/*

   Encoder  speed Test using Class

   suakii@gmail.com
*/

#include "SpeedControl.h"
//#include <TimerOne.h>
#include "src/FlexiTimer2.h"


int encoderA = 2;
int encoderB = 4;
long deltaT = 10000 ;//microsecond - 10milli second
int ticksPerRev = 2100;
int motorPlus = 5;//아두이노5번핀 -- 모터 드라이버의 A-1A
int motorMinus = 6;//아두이노 6번핀 --모터 드라이버의 A-1B
Motor lhMotor(motorPlus, motorMinus);
Encoder lhEncoder(encoderA, encoderB, deltaT, ticksPerRev);
SpeedControl lhSpeedControl(&lhMotor, &lhEncoder);

int state = 0;
int myTime = 2000;//2seconds
unsigned long pre_time = millis();
unsigned long pre_time_log = millis();
unsigned long pre_time_delay = millis();
int goalSpeed = 0;//degrees/sec
int currentSpeed = 0;

char direct;
int numChar;
void setup() {
  Serial.begin(115200);//시리얼로 값을 보내기 위한 작업

  attachInterrupt(digitalPinToInterrupt(encoderA), readLHEncoder, CHANGE);
  
  FlexiTimer2::set(10, adjust);//milli seconds 
  FlexiTimer2::start();  

  lhSpeedControl.setGains(3.0, 0.2, 0.0);

  goalSpeed = 0;
}
void loop() {
if(Serial.available()) {
  numChar = Serial.read();
  
  direct = Serial.read();//F or B
  goalSpeed = 0;
  
  while (numChar--) {
    goalSpeed = goalSpeed*10 + (Serial.read()-'0');
  }
}
  delay(100);
  if (goalSpeed >= 0) {
  if (direct == 'F')
    lhSpeedControl.setSpeed(goalSpeed);//rotate/sec
  else
    lhSpeedControl.setSpeed(-goalSpeed);//rotate/sec
 
  }
  
  
  
  //encoder speed update
  if (millis() - pre_time >= 10)
  {
    pre_time = millis();
  }
  // Log
  if (millis() - pre_time_log >= 100)
  {
    pre_time_log = millis();
  
  }
}

// updates the left hand encoder when a left hand encoder event is triggered
void readLHEncoder()
{
  lhEncoder.updateCount();
}
void adjust()
{
  lhSpeedControl.adjustPWM();
}





