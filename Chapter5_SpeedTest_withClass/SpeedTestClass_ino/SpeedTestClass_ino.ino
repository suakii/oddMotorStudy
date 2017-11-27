/*
*
 * Encoder  speed Test using Class
 * 
 * suakii@gmail.com
 */
#include "SpeedControl.h"
#include <MsTimer2.h>
#include "PID_v1.h"


int encoderA = 2;
int encoderB = 4;
long deltaT = 10000;//millisecond - 10micro second
int ticksPerRev = 2100;
int motorPlus = 5;//아두이노5번핀 -- 모터 드라이버의 A-1A                      
int motorMinus = 6;//아두이노 6번핀 --모터 드라이버의 A-1B  
Motor lhMotor(motorPlus, motorMinus);
Encoder lhEncoder(encoderA, encoderB, deltaT,ticksPerRev);
SpeedControl lhSpeedControl(&lhMotor, &lhEncoder);

int state = 0;
int myTime = 2000;//2seconds
unsigned long pre_time = millis();
unsigned long pre_time_log = millis();
unsigned long pre_time_delay = millis();
int  goalSpeed = 0;//degrees/sec

void setup() {
    Serial.begin(115200);//시리얼로 값을 보내기 위한 작업
    attachInterrupt(0, readLHEncoder, CHANGE);

    MsTimer2::set(10, adjust);//10ms
    MsTimer2::start();  
    lhSpeedControl.setGains(0.028, 0.001, 0.0006);
}
void loop() {
   
  switch(state)
  {
    case 0:
      if (millis()-pre_time_delay >= myTime)
      {
        pre_time_delay = millis();
        state = 1;
        goalSpeed = 50;
       lhSpeedControl.setSpeed(goalSpeed);//rotate/sec
      }
      break;

    case 1:
      if (millis()-pre_time_delay >= myTime)
      {
        pre_time_delay = millis();
        state = 2;
        goalSpeed = 100;
        lhSpeedControl.setSpeed(goalSpeed);//rotate/sec

      }
      break;

    case 2:
      if (millis()-pre_time_delay >= myTime)
      {
        pre_time_delay = millis();
        state = 3;
        goalSpeed = 150;
        lhSpeedControl.setSpeed(goalSpeed);//rotate/sec

      }
      break;
    case 3:
      if (millis()-pre_time_delay >= myTime)
      {
        pre_time_delay = millis();
        state = 4;
        goalSpeed = 200;
        lhSpeedControl.setSpeed(goalSpeed);//rotate/sec

      }
      break;
   
    case 4:
     if (millis()-pre_time_delay >= myTime)
      {
        pre_time_delay = millis();
        state = 5;
        goalSpeed = 300;
        lhSpeedControl.setSpeed(goalSpeed);//rotate/sec
      }
      break;
    case 5:
     if (millis()-pre_time_delay >= myTime)
      {
        pre_time_delay = millis();
        state = 6;
        goalSpeed = 350;
        lhSpeedControl.setSpeed(goalSpeed);//rotate/sec
      }
      break;
    case 6:
     if (millis()-pre_time_delay >= myTime)
      {
        pre_time_delay = millis();
        state = 0;
        goalSpeed = 0;
        lhSpeedControl.setSpeed(goalSpeed);//rotate/sec
      }
      break;
  }
  if (millis()-pre_time >= 100)
  {
       pre_time = millis();
       Serial.print(goalSpeed);
       Serial.print(" ");
       Serial.println(lhEncoder.getSpeed());
       //Serial.println(lhSpeedControl.getSpeed());
       //Serial.println();
       
       lhEncoder.getDistance();
        
  }
}

// updates the left hand encoder when a left hand encoder event is triggered
void readLHEncoder()
{
  lhEncoder.updateCount();
}


void adjust()
{
  sei();
  lhSpeedControl.adjustPWM();
}





