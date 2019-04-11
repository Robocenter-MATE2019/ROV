#include "Electromagnet.h"

Electromagnet::Electromagnet()
{
	m_pin = ELECTROMAGNET_PIN;
}

void Electromagnet::init()
{
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, HIGH);
}

void Electromagnet::write(RovData& rov_data)
{
	TIME_DEBUGER;
	if(rov_data.m_electromagnet > 0) digitalWrite(m_pin, HIGH);
	else digitalWrite(m_pin, LOW);
}