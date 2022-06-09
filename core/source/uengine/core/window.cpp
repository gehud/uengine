#include "window.h"

#include "uengine/core/windows/windows_window.h"

namespace ue 
{
	window* window::create(const window_properties& properties)
	{
		return new windows_window(properties);
	}
}