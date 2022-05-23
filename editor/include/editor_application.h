#pragma once

#include "editor_layer.h"

using namespace ue;

class editor_application : public application
{
public:
	editor_application() 
	{
		push_layer(new editor_layer());
	}
};