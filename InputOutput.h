#pragma once

#include "Input.h"
#include "Output.h"

class InputOutput 
{
public:
	virtual void init() = 0;
	virtual void read(RovData& rov_data)=0;
	virtual void write(RovData& rov_data)=0;
};

