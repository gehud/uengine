#pragma once

#include <vector>
#include <functional>

namespace ue {
	template<typename treturn, typename... targs>
	struct ifunction {
		virtual treturn invoke(const targs&... args) const = 0;

		virtual treturn operator () (const targs&... args) const {
			invoke(std::forward<const targs&>(args)...);
		}
	};

	template<typename treturn, typename... targs>
	class function_ptr final : public ifunction<treturn, targs...> {
	public:
		function_ptr(treturn(*value)(const targs&...)) : _value(value) {}

		treturn invoke(const targs&... args) const override {
			return (*_value)(std::forward<const targs&>(args)...);
		}
	private:
		treturn(*_value)(const targs&...) = nullptr;
	};

	template<typename tclass, typename treturn, typename... targs>
	class method_ptr final : public ifunction<treturn, targs...> {
	public:
		method_ptr(tclass* class_instance, treturn(tclass::* value)(const targs&...))
			: _class_instance(class_instance), _value(value) {}

		treturn invoke(const targs&... args) const override {
			return ((*_class_instance).*_value)(std::forward<const targs&>(args)...);
		}
	private:
		tclass* _class_instance = nullptr;
		treturn(tclass::* _value)(const targs&...) = nullptr;
	};

	template<typename treturn, typename... targs>
	class lambda final : public ifunction<treturn, targs...> {
	public:
		lambda(const std::function<treturn(const targs&...)>& value) : _value(value) { }

		treturn invoke(const targs&... args) const override {
			return _value(std::forward<const targs&>(args)...);
		}
	private:
		std::function<treturn(const targs&...)> _value;
	};

	template<typename... targs>
	class action final : public ifunction<void, targs...> {
	public:
		typedef ifunction<void, targs...> function_type;

		action() = default;

		~action() {
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
				_functions.erase(it);
				delete it;
			}
		}

		void operator -= (function_type* function) {
			remove(function);
		}

		void invoke(const targs&... args) const override {
			for (auto function : _functions)
				function->invoke(std::forward<const targs&>(args)...);
		}
	private:
		std::vector<function_type*> _functions;
	};
}