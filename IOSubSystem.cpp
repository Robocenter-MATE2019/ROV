#include "IOSubSystem.h"
#include "RovData.h"

IOSubSystem::IOSubSystem()
{
	int i = 0;
#if UDP_ENABLE
	m_devices[i++] = new UDPConnection;
#endif
}
void IOSubSystem::init()
{
	SUBSYSTEMSPRINT("IOSubSystem_INIT_Start");
	for (int i = 0; i < SIZE_IO_DEVICES; i++)
	{
		m_devices[i]->init();
	}
	SUBSYSTEMSPRINT("IOSubSystem_INIT_End");
}

void IOSubSystem::apply(RovData& rov_data)
{
	SUBSYSTEMSPRINT("IOSubSystem_apply_Start");
	for (int i = 0; i < SIZE_IO_DEVICES; i++)
	{
		m_devices[i]->read(rov_data);
		m_devices[i]->write(rov_data);
	}
	SUBSYSTEMSPRINT("IOSubSystem_apply_End");
}
