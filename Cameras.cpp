#include "Cameras.h"


Cameras::Cameras()
{
	//m_rotary_cam = RotaryCamera(ROTARY_CAMERA_1);
	m_rotary_cam[0] = RotaryCamera(ROTARY_CAMERA_1);
	//m_rotary_cam[1] = RotaryCamera(ROTARY_CAMERA_2);
}

void Cameras::init()
{
	//m_rotary_cam.init();
	m_rotary_cam[0].init();
	//m_rotary_cam[1].init();
}

void Cameras::write(RovData& rov_data)
{
	//m_rotary_cam.rotate(rov_data.m_rotary_camera_1);
	m_rotary_cam[0].rotate(rov_data.m_rotary_camera[0]);
	//m_rotary_cam[1].rotate(rov_data.m_rotary_camera[1]);
	//Serial.println("Cameras write");
}

