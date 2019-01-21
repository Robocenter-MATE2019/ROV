#include "IOSubSystem.h"
#include "RovData.h"

IOSubSystem::IOSubSystem()
{
	int i = 0;
	if(UDP_ENABLE) m_devices[i++] = new UDPConnection(); //во всех конктрукторах где добавляются устройства делать это через макрос #if 
	// например: #if UDP_ENABLE
	//           m_devices[i++] = new UDPConnection();
	//           #endif
	// Если ненравится 3 строчки кода вместо одной, сделай параметризованный макрос
}
void IOSubSystem::init()
{
	PRINTDEBUG("IOSubSystem_INIT_Start");
	for (int i = 0; i < SIZE_IO_DEVICES; i++)
	{
		m_devices[i]->init();
	}
	PRINTDEBUG("IOSubSystem_INIT_End");
}

void IOSubSystem::apply(RovData& rov_data)
{
	PRINTDEBUG("IOSubSystem_apply_Start");
	for (int i = 0; i < SIZE_IO_DEVICES; i++)
	{
		m_devices[i]->read(rov_data);
		m_devices[i]->write(rov_data);
	}
	PRINTDEBUG("IOSubSystem_apply_End");
}
