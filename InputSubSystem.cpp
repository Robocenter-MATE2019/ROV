#include "InputSubSystem.h"
#include "RovData.h"


InputSubSystem::InputSubSystem()
{
	int i = 0;
#if TEMPERATURE_SENSOR_ENABLE
	m_devices[i++] = new TemperatureSensor;
#endif
#if DEPTH_SENSOR_ENABLE
	m_devices[i++] = new DepthSensor;
#endif
#if IMU_ENABLE
	m_devices[i++] = new IMU;
#endif
#if METALDETECTOR_ENABLE
	m_devices[i++] = new MetalDetector;
#endif

}

void InputSubSystem::init()
{
	SUBSYSTEMSPRINT("InputSubSystem_INIT_Start");
	for (int i = 0; i < SIZE_INPUT_DEVICES; i++)
	{
		m_devices[i]->init();
	}
	SUBSYSTEMSPRINT("InputSubSystem_INIT_End");
}

void InputSubSystem::apply(RovData& rov_data)
{
	SUBSYSTEMSPRINT("InputSubSystem_apply_Start");
	for (int i = 0; i < SIZE_INPUT_DEVICES; i++)
	{
		m_devices[i]->read(rov_data);
	}
	SUBSYSTEMSPRINT("InputSubSystem_apply_End");
}
