#pragma once

#include "delegates.h"

namespace ue {
	template<typename... targs>
	class event {
	private:
		std::vector<ifunction<void, targs...>*> _functions;
	public:
		event() = default;
		event(ifunction<void, targs...>* function) {
			_functions.push_back(function);
		}

		~event() {
			for (auto function : _functions) {
				delete function;
				function = nullptr;
			}
			_functions.clear();
		}

		void assign(ifunction<void, targs...>* function) {
			_functions.assign(function);
		}

		void operator = (ifunction<void, targs...>* function) {
			assign(function);
		}

		void add(ifunction<void, targs...>* function) {
			_functions.push_back(function);
		}

		void operator += (ifunction<void, targs...>* function) {
			add(function);
		}

		void remove(ifunction<void, targs...>* function) {
			auto it = std::find(_functions.begin(), _functions.end(), function);
			if (it != _functions.end()) {
				_functions.erase(it);
				delete function;
				function = nullptr;
			}
		}

		void operator -= (ifunction<void, targs...>* function) {
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
	};

#define UE_DECLARE_EVENT(name, owner, ...) class name : public ue::event<__VA_ARGS__> { friend class owner; };
}