#pragma once

#define RELEASE
//#define DEBUG
#define ROVDATA
#define SUBSYSTEMSTEST

#ifdef RELEASE					
#define SERIALENABLE			
#define PRINTDEBUG(str)       	\
	Serial.print("FILE: ");   	\
	Serial.print(__FILE__);	  	\
	Serial.print(" | LINE: ");	\
	Serial.print(__LINE__);   	\
	Serial.print(" | MSG: "); 	\
	Serial.println(str);      	\

#else 
#define PRINTDEBUG(str)
#endif

#ifdef SUBSYSTEMSTEST			
#define SERIALENABLE			
#define SUBSYSTEMPRINT(str)		\
	Serial.print("FILE: ");		\
	Serial.print(__FILE__);		\
	Serial.print(" | LINE: ");	\
	Serial.print(__LINE__);		\
	Serial.print(" | MSG: ");	\
	Serial.println(str);		\

#else						
#define SUBSYSTEMPRINT(str)			
#endif