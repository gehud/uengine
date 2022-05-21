#include "uengine/window.h"

#include "uengine/windows/windows_window.h"

namespace ue 
{
	window* window::create(const window_properties& properties)
	{
		return new windows_window(properties);
	}
}