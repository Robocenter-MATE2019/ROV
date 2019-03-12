/*
 Name:		TestAr.ino
 Created:	13.11.2018 17:14:10
 Author:	Виталий
*/

#include <Wire.h>
#include <Servo.h>
#include <OneWire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Arduino.h>
#include "Rov.h"
#include "Timer.h"

Rov rov;

void setup()
{
#ifdef SERIALENABLE
	Serial.begin(115200);
#endif
	//Serial.begin(115200);
	rov.init();
	//Serial.println("start");
}

Timer t;

void loop() 
{
#ifdef SERIALENABLE
	Serial.println("=========================================");
#endif 
	//t.start();
	rov.run();
	//Serial.print("timer = ");
	//Serial.println(t.elapsed());
}
