#pragma once

#include <memory>

namespace ue 
{
	template<typename t>
	using reference = std::shared_ptr<t>;

	template<typename t>
	using scope = std::unique_ptr<t>;
}