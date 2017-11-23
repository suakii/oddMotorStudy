/*
 * one cycle rotation
 * suakii@gmail.com
 */
 
int pulses;    
int pulsesChanged;                          
int encoderA = 2;//아두이노2번핀 -- 모터의 3번핀 Encoder A Phase
int encoderB = 4;//아두이노4번핀 --- 모터의 4번핀 Encoder B Phase
int motorPlus = 5;//아두이노5번핀 -- 모터 드라이버의 A-1A                      
int motorMinus = 6;//아두이노 6번핀 --모터 드라이버의 A-1B  

int total =2100;//모터가 1회전 하기 위한 펄스 수                      
int motorSpeed = 200;//모터 구동 pwm value
void setup() {
  pinMode(encoderA, INPUT_PULLUP);//인코더 값을 읽기 위하여 내부 풀업 저항 사용 
  pinMode(encoderB, INPUT_PULLUP);
 
  /*
   0번은 아두이노에서는 디지털2번핀에 부여된 인터럽트 기능을 말하는 것임
   여기에서의 인터럽트는 소프트웨어적이 아닌 하드웨어 인터럽트를 감지하는 것이며
   마치 윈도우의 callback 함수처럼 2번핀에 신호의 CHANGE가 발생하였을 때(즉 엔코더가 회전하면서 rising, falling)
   특정함 수를 연결하는 것임 여기서는 A_CHANGE
  */
  attachInterrupt(0, A_CHANGE, CHANGE);//
   //attachInterrupt(digitalPinToInterrupt(interruptPin), A_CHANGE, CHANGE);//함수로 핀을 지정해도 됨.

  analogWrite(motorPlus, 0);//초기 모터 정지
  analogWrite(motorMinus, 0);
 
  Serial.begin(115200);//시리얼로 값을 보내기 위한 작업
  
}
void loop() {
 
  if (pulses == total)
    analogWrite(motorPlus, 0);//모터 정지
  else {
    if (pulses > total)
      analogWrite(motorPlus, 0);//모터 정지
    else if (pulses < total) 
      analogWrite(motorPlus, motorSpeed);//모터 구동
  } 
  if (pulsesChanged != 0) {//펄스 값의 변화가 발생했다면 이 값을 전송
    
	Serial.print(pulses);
    Serial.print("\n");
    pulsesChanged = 0;
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
  pulsesChanged = 1;
}

