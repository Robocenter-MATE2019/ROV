#pragma once

//#define RELEASE
//#define DEBUG
//#define ROVDATA
//#define SUBSYSTEMSTEST
//#define DEVICESTEST

#ifdef SUBSYSTEMSTEST					
#define SERIALENABLE			
#define SUBSYSTEMSPRINT(str)    \
	Serial.print("FILE: ");   	\
	Serial.print(String(__FILE__).substring(String(__FILE__).lastIndexOf('\\') + 1)); 	\
	Serial.print(" | LINE: ");	\
	Serial.print(__LINE__);   	\
	Serial.print(" | MSG: "); 	\
	Serial.println(str);      	\

#else 
#define SUBSYSTEMSPRINT(str)
#endif

#ifdef DEBUG					
#define SERIALENABLE			
#define PRINTDEBUG(str)       	\
	Serial.print("FILE: ");   	\
	Serial.print(String(__FILE__).substring(String(__FILE__).lastIndexOf('\\') + 1)); 	\
	Serial.print(" | LINE: ");	\
	Serial.print(__LINE__);   	\
	Serial.print(" | MSG: "); 	\
	Serial.println(str);      	\

#else 
#define PRINTDEBUG(str)
#endif

#ifdef DEVICESTEST					
#define SERIALENABLE			
#define DEVICESPRINT(str)       	\
	Serial.print("FILE: ");   	\
	Serial.print(String(__FILE__).substring(String(__FILE__).lastIndexOf('\\') + 1)); 	\
	Serial.print(" | LINE: ");	\
	Serial.print(__LINE__);   	\
	Serial.print(" | MSG: "); 	\
	Serial.println(str);      	\

#else 
#define DEVICESPRINT(str)
#endif
