#pragma once

#include "RovData.h"

class Output
{
public:
	virtual void init() = 0;
	virtual void write(RovData& rov_data) = 0;
};

