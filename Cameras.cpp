#include "Cameras.h"


Cameras::Cameras()
{
	m_rotary_cam[0] = RotaryCamera(ROTARY_CAMERA_1);
	m_rotary_cam[1] = RotaryCamera(ROTARY_CAMERA_2);
}

void Cameras::init()
{
	m_rotary_cam[0].init();
	m_rotary_cam[1].init();
	m_rotary_cam[0].setRotationTime(30);
	m_rotary_cam[1].setRotationTime(30);
	DEVICESPRINT("Cameras.init()");
}

void Cameras::write(RovData& rov_data)
{
	TIME_DEBUGER;
	DEVICESPRINT("Cameras.write()");
	m_rotary_cam[0].rotate(rov_data.m_rotary_camera[0]);
	m_rotary_cam[1].rotate(rov_data.m_rotary_camera[1]);
}

