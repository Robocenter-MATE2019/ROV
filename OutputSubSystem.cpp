#include "OutputSubSystem.h"
#include "RovData.h"


 OutputSubSystem::OutputSubSystem()
{
	int i = 0;
#if MANIPULATOR_ENABLE
	m_devices.create<ROVBuilderManipulator>();
#endif
#if THRUSTERSSUBSYSTEM_ENABLE
	m_devices.create<ThrustersSubSystem>();
#endif
#if ROTARYCAMERA_ENABLE
	m_devices.create<Cameras>();
#endif
#if COILER_ENABLE
	m_devices.create<Coiler>(); 
#endif
#if HELIX_ENABLE
	m_devices.create<Helix>();
#endif
#if ELECTROMAGNET_ENABLE
	m_devices.create<Electromagnet>();
#endif
}

void OutputSubSystem::init()
{
	SUBSYSTEMSPRINT("OutputSubSystem_INIT_Start");
	invoke_all(m_devices, &Output::init);
	SUBSYSTEMSPRINT("OutputSubSystem_INIT_End");
}

void OutputSubSystem::apply(RovData& rov_data)
{
	SUBSYSTEMSPRINT("OutputSubSystem_apply_Start");
	invoke_all(m_devices, &Output::write, rov_data);
	SUBSYSTEMSPRINT("OutputSubSystem_apply_End");
}
