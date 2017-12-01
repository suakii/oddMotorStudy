// Motor
// by Andrew Kramer

// controls direction and pwm input to a DC motor
// modified by Jonghwa Park(suakii@gmail.com)
#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
public:
	Motor(int motorPlus, int motorMinus);
	void setFwd(int level);
	void setBack(int level);
	void setStop();
private:
	int _motorPlus, _motorMinus;//arduino 5, 6 just one motor
};

#endif