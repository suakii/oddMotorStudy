// Encoder
// by Andrew Kramer

// initializes an object to read input from a shaft encoder and
// track the number of encoder ticks using interrupts

//modified by Jonghwa Park(suakii@gmail.com)
#include "Encoder.h"
#include "Arduino.h"

// accepts three ints and a long as parameters:
//      encoderA - the digital pin used to read encoder output A
//                 this MUST be an interrupt pin
//      구입한 모터의 A Phase를 출력해주는 것이며 이는 아두이노의 2번 핀에 연결이 된다.
//      encoderB - the digital pin used to read encoder output B
//      구입한 모터의 B Phase를 뜻하면 모터 번호 4번, 아두이노에는 4번 핀에 연결한다.
//        deltaT - the time interval used to calculate output shaft speed
//                 in microseconds
//   ticksPerRev - the number of encoder ticks per revolution of 
//                 the output shaft
Encoder::Encoder(int encoderA, int encoderB, 
				 long deltaT, int ticksPerRev)
{
	_encoderA = encoderA;
	_encoderB = encoderB;
	_count = 0;
	_oldCount = 0;
	_newCount = 0;
	_totalCount = 0;
	_lastSpeed = 0;
	_deltaT = deltaT;
	_degPerTick = 360.0 / (double)ticksPerRev;
	pinMode(_encoderA, INPUT_PULLUP);//suakii
	pinMode(_encoderB, INPUT_PULLUP);//suakii
}

// returns the average speed of the motor output shaft in degrees/second
// over the last _deltaT microseconds
// MUST be called every _deltaT microseconds to return accurate speed
int Encoder::getSpeed()
{  
	return _lastSpeed;
}

int Encoder::updateSpeed()
{
	_oldCount = _newCount;
	_newCount = _count;
	// calculate number of ticks elapsed since in last deltaT
  difference = _newCount - _oldCount;
  

 // update _totalCount
	_totalCount += difference;
	int degPerSec;
	// calculate new speed if _count has not overflowed 
	if (difference < 50000 && difference > -50000)
	{
		double deltaTInSec = (double)1000000 / (double)_deltaT;
		double ticksPerSec = (double)difference * (double)deltaTInSec;
		degPerSec = ticksPerSec * _degPerTick;
		_lastSpeed = degPerSec;
	}
	else // use previous speed if overflow has occurred in _count
	{
		degPerSec = _lastSpeed;
	}
  
	return degPerSec;
}

// returns net distance rotated by the motor's output shaft in degrees
// since the last call to getDistance()
// should be called regularly to prevent overflows in _totalCount
int Encoder::getDistance()
{
	int distance = _degPerTick * _totalCount;
	_totalCount = 0;
	return distance;
}

// updates the _count when an encoder event occurs
// must be called using a pin change interrupt from the client sketch
void Encoder::updateCount()
{
	if (digitalRead(_encoderA) == HIGH)
	{
		if (digitalRead(_encoderB) == LOW)
			_count--;
		else
			_count++;
	}
	else
	{
		if (digitalRead(_encoderB) == LOW)
			_count++;
		else
			_count--;
	}
}

int Encoder::getCount() 
{
  return _count;
}

