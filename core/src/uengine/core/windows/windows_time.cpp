#include "windows_time.h"

#include <GLFW/glfw3.h>

namespace ue 
{
    double windows_time::get_time_impl() const
    {
        return glfwGetTime();
    }
}