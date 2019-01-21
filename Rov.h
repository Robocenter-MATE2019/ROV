#pragma once

#include "SubSystem.h"
#include "RovData.h"
#include "Config.h"

class Rov {
public:
	Rov();
	void init();
	void run();
	RovData m_rov_data;
	SubSystem* m_subsystem[SUBSYSTEM_SIZE];
};
