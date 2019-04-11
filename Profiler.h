#pragma once

class Profiler {
public:
	Profiler() {
		m_time.start();
	}
	~Profiler() {
		Serial.print(" timer = ");
		Serial.println(m_time.elapsed());
	}
private:
	Timer m_time;
};
