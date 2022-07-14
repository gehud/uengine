#include "math.h"

#include <limits>

namespace ue {
	const float math::epsilon = std::numeric_limits<float>::epsilon();
	const float math::pi = 3.1415927f;
}