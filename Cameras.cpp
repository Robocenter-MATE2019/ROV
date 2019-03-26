#include "Cameras.h"


Cameras::Cameras()
{
	m_rotary_cam[0] = RotaryCamera(ROTARY_CAMERA_1);
	//m_rotary_cam[1] = RotaryCamera(ROTARY_CAMERA_2);
}

void Cameras::init()
{
	m_rotary_cam[0].init();
	//m_rotary_cam[1].init();
	DEVICESPRINT("Cameras.init()");
}

void Cameras::write(RovData& rov_data)
{
	m_rotary_cam[0].rotate(rov_data.m_rotary_camera[0]);
	//m_rotary_cam[1].rotate(rov_data.m_rotary_camera[1]);
	DEVICESPRINT("Cameras.write()");
#ifdef TIMERS
	if (timer_macros.elapsed() > 1000)
	{
		Serial.println(__FILE__);
		Serial.println(__LINE__);
		Serial.print("LAG!!! time = ");
		Serial.println(timer_macros.elapsed());
		delay(10000000000000000);
	}
	timer_macros.start();
#endif
}

