#include "IOSubSystem.h"
#include "RovData.h"

IOSubSystem::IOSubSystem()
{
#if UDP_ENABLE
	m_devices.create<UDPConnection>();
#endif
}
void IOSubSystem::init()
{
	SUBSYSTEMSPRINT("IOSubSystem_INIT_Start");
	invoke_all(m_devices, &InputOutput::init);
	SUBSYSTEMSPRINT("IOSubSystem_INIT_End");
}

void IOSubSystem::apply(RovData& rov_data)
{
	SUBSYSTEMSPRINT("IOSubSystem_apply_Start");
	invoke_all(m_devices, &InputOutput::write, rov_data);
	invoke_all(m_devices, &InputOutput::read, rov_data);
	SUBSYSTEMSPRINT("IOSubSystem_apply_End");
}
