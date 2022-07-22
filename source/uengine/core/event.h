#pragma once

#include "uengine/core/delegates.h"

namespace ue {
	template<typename... targs>
	class event {
	public:
		typedef ifunction<void, targs...> function_type;

		event() = default;

		~event() {
			for (auto function : _functions)
				delete function;
			_functions.clear();
		}

		void assign(function_type* function) {
			_functions.assign(function);
		}

		void operator = (function_type* function) {
			assign(function);
		}

		void add(function_type* function) {
			_functions.push_back(function);
		}

		void operator += (function_type* function) {
			add(function);
		}

		void remove(function_type* function) {
			auto it = std::find(_functions.begin(), _functions.end(), function);
			if (it != _functions.end()) {
				delete it;
				_functions.erase(it);
			}
		}

		void operator -= (function_type* function) {
			remove(function);
		}
	protected:
		void invoke(const targs&... args) const {
			for (auto function : _functions)
				function->invoke(std::forward<const targs&>(args)...);
		}

		void operator () (const targs&... args) const {
			invoke(std::forward<const targs&>(args)...);
		}
	private:
		std::vector<function_type*> _functions;
	};

#define UE_DECLARE_EVENT(name, owner, ...) class name : public ue::event<__VA_ARGS__> { friend class owner; };
}