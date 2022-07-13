#include "matrix3x3.h"

namespace ue {
	const matrix3x3 matrix3x3::zero {};

	const matrix3x3 matrix3x3::one { 
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f 
	};

	const matrix3x3 matrix3x3::identity { 
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f 
	};
}