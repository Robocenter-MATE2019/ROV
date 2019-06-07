/*
 Name:		TestAr.ino
 Created:	13.11.2018 17:14:10
 Author:	Виталий
*/

#include <Ethernet.h>
#include <Arduino.h>
#include "Rov.h"
#include "Timer.h"
#include "Profiler.h"
#include "BrushlessMotor.h"

Rov rov;

void setup()
{
#ifdef SERIALENABLE
	Serial.begin(115200);
#endif
	//Serial.begin(115200);
	rov.init();
}

void loop() 
{
	rov.run();
}

