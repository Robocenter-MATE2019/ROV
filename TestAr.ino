/*
 Name:		TestAr.ino
 Created:	13.11.2018 17:14:10
 Author:	Виталий
*/

#include <Wire.h>
#include <Servo.h>
#include <OneWire.h>
#include <SPI.h>
#include <Arduino.h>
#include "Rov.h"
#include "Timer.h"

Rov rov;

void setup()
{
#ifdef SERIALENABLE
	Serial.begin(115200);
#endif
	Serial.begin(115200);
	rov.init();
	//Serial.println("start");
}

Timer t;
int i = 0;
class Profiler {
public:
	Profiler() {
		m_time.start();
	}
	~Profiler() {
		Serial.print("it = ");
		Serial.print(i++);
		Serial.print("; timer = ");
		Serial.println(m_time.elapsed());
	}
private:
	Timer m_time;
};


void loop() 
{
	//Profiler p;
#ifdef SERIALENABLE
	Serial.println("=========================================");
#endif 
	rov.run();
}
