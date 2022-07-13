#pragma once

#include <memory.h>

namespace ue {
	struct matrix3x3 {
		static const matrix3x3 zero;
		static const matrix3x3 one;
		static const matrix3x3 identity;

		matrix3x3() {
			memset(_values, 0, 9);
		}

		matrix3x3(float x0, float y0, float z0,
				  float x1, float y1, float z1,
				  float x2, float y2, float z2) {
			_values[0] = x0; _values[1] = y0; _values[2] = z0;
			_values[3] = x1; _values[4] = y1; _values[5] = z1;
			_values[6] = x2; _values[7] = y2; _values[8] = z2;
		}

		float determinant() const {
			// Rule of Sarrus: https://en.wikipedia.org/wiki/Rule_of_Sarrus.
			return (_values[0] * _values[4] * _values[8])
			     + (_values[1] * _values[5] * _values[6])
			     + (_values[2] * _values[3] * _values[7])
			     - (_values[6] * _values[4] * _values[2])
			     - (_values[7] * _values[5] * _values[0])
			     - (_values[8] * _values[3] * _values[1]);
		}
	private:
		float _values[9];
	};
}