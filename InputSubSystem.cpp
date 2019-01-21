#include "InputSubSystem.h"
#include "RovData.h"


InputSubSystem::InputSubSystem()
{
	int i = 0;
	if (IMU_ENABLE) {}
	if (DnT_ENABLE) {}
}

void InputSubSystem::init()
{
	PRINTDEBUG("InputSubSystem_INIT_Start");
	for (int i = 0; i < SIZE_INPUT_DEVICES; i++)
	{
		m_devices[i]->init();
	}
	PRINTDEBUG("InputSubSystem_INIT_End");
}

void InputSubSystem::apply(RovData& rov_data)
{
	PRINTDEBUG("InputSubSystem_apply_Start");
	for (int i = 0; i < SIZE_INPUT_DEVICES; i++)
	{
		m_devices[i]->read(rov_data);
	}
	PRINTDEBUG("InputSubSystem_apply_End");
}
