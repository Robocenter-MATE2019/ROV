#include "RotaryCamera.h"

RotaryCamera::RotaryCamera()
{
}

RotaryCamera::RotaryCamera(int8_t pin)
{
	m_pin = pin;
	defAngle = 90;
}

void RotaryCamera::init()
{
	m_driver.attach(m_pin);
	timer.start();
	m_driver.write(defAngle);
	m_angle = defAngle;
}

RotaryCamera::~RotaryCamera()
{
	m_driver.detach();
}

void RotaryCamera::rotate(int8_t angle)
{	
	m_lastangle = angle != m_lastangle ? angle : m_lastangle;
	if (timer.elapsed() > 30)
	{
		m_angle += m_lastangle;
		timer.start();
		m_angle = constrain(m_angle, 25, 165);
		m_driver.write(m_angle);
	}
}
