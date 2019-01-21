#include "OutputSubSystem.h"
#include "RovData.h"


 OutputSubSystem::OutputSubSystem()
{
	int i = 0;
#if MANIPULATOR_ENABLE
	m_devices[i++] = new ROVBuilderManipulator();
#endif
#if THRUSTERSSUBSYSTEM_ENABLE
	m_devices[i++] = new ThrustersSubSystem();
#endif
#if ROTARYCAMERA_ENABLE
	m_devices[i++] = new Cameras();
#endif

}

void OutputSubSystem::init()
{
	//Serial.println("OutputSubSystem_INIT_Start");
	for (int i = 0; i < SIZE_OUTPUT_DEVICES; i++)
	{
		m_devices[i]->init();
	}
	//Serial.println("OutputSubSystem_INIT_End");
}

void OutputSubSystem::apply(RovData& rov_data)
{
	//Serial.println("OutputSubSystem_apply_Start");
	for (int i = 0; i < SIZE_OUTPUT_DEVICES; i++)
	{
		m_devices[i]->write(rov_data);
	}
	//Serial.println("OutputSubSystem_apply_End");
}