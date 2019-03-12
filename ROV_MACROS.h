#pragma once

//#define RELEASE
//#define DEBUG
//#define ROVDATA
//#define SUBSYSTEMSTEST
//#define DEVICESTEST
#define DATAINFO

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


#ifdef DATAINFO
#define SERIALENABLE
#define ROVDATAPRINT					\
Serial.print("rov_data.temperature = ");\
Serial.println(m_rov_data.m_temperature);		\
Serial.print("rov_data.depth = ");\
Serial.println(m_rov_data.m_depth);		\
Serial.print("rov_data.yaw = ");		\
Serial.println(m_rov_data.m_yaw);				\
Serial.print("rov_data.pitch = ");		\
Serial.println(m_rov_data.m_pitch);			\
Serial.print("rov_data.roll = ");		\
Serial.println(m_rov_data.m_roll);			\

#else
#define ROVDATAPRINT
#endif
