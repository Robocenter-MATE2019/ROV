#include "UARTCommunicator.h"
#include <Arduino.h>

void UARTCommunicator::init()
{
	Serial.begin(115200);
}

bool UARTCommunicator::read(Axis & axis)
{
	if (Serial.available() > 4)
	{
		int8_t asterisk = 0;
		while (asterisk != '*')
		{
			asterisk = Serial.read();
			if (Serial.available() == 0)
			{
				return false;
			}
		}
		String axis_ = Serial.readStringUntil('-');
		if (axis_.length() != 3)
		{
			return false;
		}

		axis.x = axis_[0];
		axis.y = axis_[1];
		axis.z = axis_[2];
		
		Serial.readString();
		return true;
	}
	return false;
}