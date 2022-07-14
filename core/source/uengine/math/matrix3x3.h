#pragma once

#include "vector3.h"

#define UE_MATRICES_COLUMN_MAJOR

namespace ue {
	struct matrix3x3 {
	public:
		matrix3x3() = default;

		matrix3x3(float x0, float y0, float z0,
				  float x1, float y1, float z1,
				  float x2, float y2, float z2) {
#if defined(UE_MATRICES_ROW_MAJOR)
			_values[0][0] = x0; _values[0][1] = y0; _values[0][2] = z0;
			_values[1][0] = x1; _values[1][1] = y1; _values[1][2] = z1;
			_values[2][0] = x2; _values[2][1] = y2; _values[2][2] = z2;
#elif defined(UE_MATRICES_COLUMN_MAJOR)
			_values[0][0] = x0; _values[1][0] = y0; _values[2][0] = z0;
			_values[0][1] = x1; _values[1][1] = y1; _values[2][1] = z1;
			_values[0][2] = x2; _values[1][2] = y2; _values[2][2] = z2;
#endif
		}

		float determinant() const {
			return _values[0][0] * _values[1][1] * _values[2][2]
				 + _values[2][0] * _values[0][1] * _values[1][2]
				 + _values[1][0] * _values[2][1] * _values[0][2]
				 - _values[2][0] * _values[1][1] * _values[0][2]
				 - _values[0][0] * _values[2][1] * _values[1][2]
				 - _values[1][0] * _values[0][1] * _values[2][2];
		}
	private:
		vector3 _values[3];
	};
}