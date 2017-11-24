/*
 * Speed Test simple
 * class를 사용하지 않는 형태임 
 * 다음 작업에서는 클래스를 사용한 형태로 변환
 * suakii@gmail.com
 * 아래 코드 중 switch 부분은
 * [canDynamix] 모터 속도 테스트  (광주로봇동호회_[깡통로봇연구소]) |작성자 Baram
*  코드를 참고하여 작성하였음을 밝힙니다.
 */
#include <MsTimer2.h>

int pulses, currentPulses;
int motorSpeed;
    
int encoderA = 2;//아두이노2번핀 -- 모터의 3번핀 Encoder A Phase
int encoderB = 4;//아두이노4번핀 --- 모터의 4번핀 Encoder B Phase
int motorPlus = 5;//아두이노5번핀 -- 모터 드라이버의 A-1A                      
int motorMinus = 6;//아두이노 6번핀 --모터 드라이버의 A-1B  

int state = 0;
unsigned long pre_time = millis();
unsigned long pre_time_delay = millis();
int  pwm = 0;



void setup() {
  pinMode(encoderA, INPUT_PULLUP);//인코더 값을 읽기 위하여 내부 풀업 저항 사용 
  pinMode(encoderB, INPUT_PULLUP);
 
  
  attachInterrupt(0, A_CHANGE, CHANGE);//
   
  analogWrite(motorPlus, 0);//초기 모터 정지
  analogWrite(motorMinus, 0);
 
  Serial.begin(115200);//시리얼로 값을 보내기 위한 작업
 
}
bool pulsesChanged = false;

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
        analogWrite(motorPlus, pwm);
      }
      break;

    case 1:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 2;
        pwm = 100;
        analogWrite(motorPlus, pwm);
      }
      break;

    case 2:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 3;
        pwm = 150;
        analogWrite(motorPlus, pwm);
      }
      break;
    case 3:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 4;
        pwm = 200;
        analogWrite(motorPlus, pwm);
      }
      break;
    case 4:
     if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 5;
        pwm = 250;
        analogWrite(motorPlus, pwm);
      }
      break;
       case 5:
      if (millis()-pre_time_delay >= 2000)
      {
        pre_time_delay = millis();
        state = 0;
        pwm = 0;
        analogWrite(motorPlus, pwm);        
      }
      break;    
  }
	//100ms 당  측정된 회전수 값을 시리얼로 전송
	//즉 셋팅한 pwm value와 실제 회전수의 관계를 보기 위한 것임.
  if (millis()-pre_time >= 100)
  {
    pre_time = millis();
	motorSpeed = pulses - currentPulses;//속도의 정의를 100ms당 회전수로 정의
	currentPulses = pulses;
    Serial.print(pwm);
    Serial.print(" ");    
    Serial.println(motorSpeed);
        
  }
  
}

void A_CHANGE() {                                     
  if ( digitalRead(encoderB) == 0 ) {
    if ( digitalRead(encoderA) == 0 ) {
      // A fall, B is low
      pulses--; // Moving forward
    } else {
      // A rise, B is high
      pulses++; // Moving reverse
    }
  } else {
    if ( digitalRead(encoderA) == 0 ) {
      pulses++; // Moving reverse
    } else {
      // A rise, B is low
      pulses--; // Moving forward
    }
  }
  pulsesChanged = true;

}



