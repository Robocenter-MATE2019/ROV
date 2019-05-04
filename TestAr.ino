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

Rov rov;

void setup()
{
#ifdef SERIALENABLE
	Serial.begin(115200);
#endif
	rov.init();
}

void loop() 
{
	//Profiler p;
//#ifdef SERIALENABLE
//	Serial.println("=========================================");
//#endif 
	rov.run();
}
