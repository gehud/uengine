#include "uengine/math/math.h"

#include <limits>
#include <numbers>

namespace ue {
	const float math::pi = std::numbers::pi_v<float>;
	const float math::epsilon = std::numeric_limits<float>::epsilon();
	const float math::positive_infinity = std::numeric_limits<float>::infinity();
	const float math::negative_infinity = -std::numeric_limits<float>::infinity();
}