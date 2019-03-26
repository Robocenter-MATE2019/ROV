#include"TemperatureSensor.h"

TemperatureSensor::TemperatureSensor() : m_wire(TEMPERATURE_SENSOR) {}

void TemperatureSensor::init()
{
	DEVICESPRINT("TenperatureSensor.init()");
}

void TemperatureSensor::read(RovData& rov_data)
{
	getTemperature(rov_data);
	DEVICESPRINT("TenperatureSensor.read()");
#ifdef TIMERS
	if (timer_macros.elapsed() > 1000)
	{
		Serial.println(__FILE__);
		Serial.print("LAG!!! time = ");
		Serial.println(timer_macros.elapsed());
		delay(10000000000000000);
	}
	timer_macros.start();
#endif
}

float TemperatureSensor::getTemperature(RovData& rov_data)
{
	byte i;
	byte present = 0;
	byte type_s;
	byte data[12];
	byte addr[8];
	if (!m_wire.search(addr)) {
		m_wire.reset_search();
		rov_data.m_temperature = m_result;
		return m_result;
	}
	if (OneWire::crc8(addr, 7) != addr[7]) {
		rov_data.m_temperature = m_result;
		return m_result;
	}
	m_wire.reset();
	m_wire.select(addr);
	m_wire.write(0x44, 1);
	if (!m_timer.is_started())
	{
		m_timer.start();
	}
	if (m_timer.elapsed() > 1000)
	{
		present = m_wire.reset();
		m_wire.select(addr);
		m_wire.write(0xBE);
		for (i = 0; i < 9; i++) {
			data[i] = m_wire.read();
		}
		int16_t raw = (data[1] << 8) | data[0];
		if (type_s) {
			raw = raw << 3;
			if (data[7] == 0x10)
			{
				raw = (raw & 0xFFF0) + 12 - data[6];
			}
		}
		else {
			byte cfg = (data[4] & 0x60);
			if (cfg == 0x00) raw = raw & ~7;
			else if (cfg == 0x20) raw = raw & ~3;
			else if (cfg == 0x40) raw = raw & ~1;
		}
		if((float)raw / 16.0 > 0) m_result = (float)raw / 16.0;
		m_timer.stop();
		rov_data.m_temperature = m_result;
		return m_result;
	}
}
