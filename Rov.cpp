#include "Rov.h"
#include "OutputSubSystem.h"
#include "InputSubSystem.h"
#include "IOSubSystem.h"

Rov::Rov()
{
#if OUTPUTSUBSYSTEM_ENABLE
	m_subsystem.create<OutputSubSystem>();
#endif
#if INPUTSUBSYSTEM_ENABLE
	m_subsystem.create<InputSubSystem>();
#endif
#if IOSUBSYSTEM_ENABLE
	m_subsystem.create<IOSubSystem>();
#endif
}

void Rov::init()
{
	invoke_all(m_subsystem, &SubSystem::init);
#if THRUSTERSSUBSYSTEM_ENABLE
	delay(10000);
#endif
}

void Rov::run()
{
	invoke_all(m_subsystem, &SubSystem::apply, m_rov_data);
	ROVDATAPRINT;
}


