#include "OutputSubSystem.h"
#include "RovData.h"


 OutputSubSystem::OutputSubSystem()
{
	int i = 0;
#if MANIPULATOR_ENABLE
	m_devices[i++] = new ROVBuilderManipulator;
#endif
#if THRUSTERSSUBSYSTEM_ENABLE
	m_devices[i++] = new ThrustersSubSystem;
#endif
#if ROTARYCAMERA_ENABLE
	m_devices[i++] = new Cameras;
#endif
#if COILER_ENABLE
	m_devices[i++] = new Coiler;
#endif 
#if HELIX_ENABLE
	m_devices[i++] = new Helix;
#endif
#if ELECTROMAGNET_ENABLE
	m_devices[i++] = new Electromagnet;
#endif
}

void OutputSubSystem::init()
{
	SUBSYSTEMSPRINT("OutputSubSystem_INIT_Start");
	for (int i = 0; i < SIZE_OUTPUT_DEVICES; i++)
	{
		m_devices[i]->init();
	}
	SUBSYSTEMSPRINT("OutputSubSystem_INIT_End");
}

void OutputSubSystem::apply(RovData& rov_data)
{
	SUBSYSTEMSPRINT("OutputSubSystem_apply_Start");
	for (int i = 0; i < SIZE_OUTPUT_DEVICES; i++)
	{
		m_devices[i]->write(rov_data);
	}
	SUBSYSTEMSPRINT("OutputSubSystem_apply_End");
}
