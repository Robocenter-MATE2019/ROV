#include "InputSubSystem.h"
#include "RovData.h"


InputSubSystem::InputSubSystem()
{
	int i = 0;
#if TEMPERATURE_SENSOR_ENABLE
	m_devices.create<TemperatureSensor>();
#endif
#if DEPTH_SENSOR_ENABLE
	m_devices.create<DepthSensor>();
#endif
#if IMU_ENABLE
	m_devices.create<IMU>();
#endif
#if METALDETECTOR_ENABLE
	m_devices.create<MetalDetector>();
#endif

}

void InputSubSystem::init()
{
	SUBSYSTEMSPRINT("InputSubSystem_INIT_Start");
	invoke_all(m_devices, &Input::init);
	SUBSYSTEMSPRINT("InputSubSystem_INIT_End");
}

void InputSubSystem::apply(RovData& rov_data)
{
	SUBSYSTEMSPRINT("InputSubSystem_apply_Start");
	invoke_all(m_devices, &Input::read, rov_data);
	SUBSYSTEMSPRINT("InputSubSystem_apply_End");
}
