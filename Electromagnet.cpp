#include "Electromagnet.h"

Electromagnet::Electromagnet()
{
	m_pin = ELECTROMAGNET_PIN;
}

void Electromagnet::init()
{
	pinMode(m_pin, OUTPUT);
}

void Electromagnet::write(RovData& rov_data)
{
	analogWrite(m_pin, rov_data.m_electromagnet);
}