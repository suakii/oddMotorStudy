/*
 * Speed Test using Class
 * 
 * suakii@gmail.com
 */

#include "Motor.h"
#include "Encoder.h"

#include <MsTimer2.h>

int encoderA = 2;
int encoderB = 4;
long deltaT = 100000;//millisecond
int ticksPerRev = 2100;
int motorPlus = 5;//아두이노5번핀 -- 모터 드라이버의 A-1A                      
int motorMinus = 6;//아두이노 6번핀 --모터 드라이버의 A-1B  
Motor lhMotor(motorPlus, motorMinus);
Encoder lhEncoder(encoderA, encoderB, deltaT,ticksPerRev);

int state = 0;
unsigned long pre_time = millis();
unsigned long pre_time_delay = millis();
int  pwm = 0;
int motorSpeed;


void setup() {
    Serial.begin(115200);//시리얼로 값을 보내기 위한 작업
    attachInterrupt(0, readLHEncoder, CHANGE);
}
void loop() {
   

 /*
  2초마다 pwm value를 높이면서 모터의 목표 속도를 증가시키고 있음.
  여기에서 목표 속도란 얼밀히 말하면 m/s, rad/s 등이 아닌 0~255 사이의 pwm value임.
  */
  switch(state)
  {
    case 0:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 1;
        pwm = 50;
        lhMotor.setFwd(pwm);        
      }
      break;

    case 1:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 2;
        pwm = 100;
        lhMotor.setFwd(pwm);        
    }
      break;

    case 2:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 3;
        pwm = 150;
        lhMotor.setFwd(pwm);        
    }
      break;
    case 3:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 4;
        pwm = 200;
        lhMotor.setFwd(pwm);        
    }
      break;
    case 4:
     if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 5;
        pwm = 250;
        lhMotor.setFwd(pwm);        
    }
      break;
       case 5:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 0;
        pwm = 0;
        lhMotor.setFwd(pwm);        
    }
      break;    
  }
	//100ms 당  측정된 회전수 값을 시리얼로 전송
	//즉 셋팅한 pwm value와 실제 회전수의 관계를 보기 위한 것임.
  if (millis()-pre_time >= 100)
  {
    pre_time = millis();
	  motorSpeed = lhEncoder.getSpeed();//속도의 정의를 100ms당 회전수로 정의
	  Serial.print(pwm);
    Serial.print(" ");    
    Serial.println(motorSpeed);    
  }
}

// updates the left hand encoder when a left hand encoder event is triggered
void readLHEncoder()
{
  lhEncoder.updateCount();
}
