#include "Rov.h"
#include "OutputSubSystem.h"
#include "InputSubSystem.h"
#include "IOSubSystem.h"

Rov::Rov()
{
	int i = 0;
#if OUTPUTSUBSYSTEM_ENABLE
	m_subsystem[i++] = new OutputSubSystem;
#endif
#if INPUTSUBSYSTEM_ENABLE
	m_subsystem[i++] = new InputSubSystem;
#endif
#if IOSUBSYSTEM_ENABLE
	m_subsystem[i++] = new IOSubSystem;
#endif
}


void Rov::init()
{
	for (int i = 0; i < SUBSYSTEM_SIZE; i++)
	{
		m_subsystem[i]->init();
	}
	//delay(10000);
}

void Rov::run()
{
	for (int i = 0; i < SUBSYSTEM_SIZE; i++)
	{
		m_subsystem[i]->apply(m_rov_data);
		ROVDATAPRINT;
	}
}


