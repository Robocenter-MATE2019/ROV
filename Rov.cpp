#include "Rov.h"
#include "OutputSubSystem.h"
#include "InputSubSystem.h"
#include "IOSubSystem.h"

Rov::Rov()
{
	int i = 0;
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
	//delay(10000);
}

void Rov::run()
{
	invoke_all(m_subsystem, &SubSystem::apply, m_rov_data);
	ROVDATAPRINT;
}


