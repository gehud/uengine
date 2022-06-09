#pragma once

#include "uengine/core/time.h"

namespace ue 
{
	class windows_time : public time 
	{
	protected:
		double get_time_impl() const override;
	};
}