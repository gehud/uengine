#pragma once

namespace ue {
	template<int L, typename T> struct vector;

	template<int L, typename T>
	constexpr vector<L, T> operator + (const vector<L, T>& v) {
		return v;
	}
}