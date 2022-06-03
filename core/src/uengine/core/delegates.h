#pragma once

#include <vector>
#include <functional>

namespace ue 
{
	template<typename treturn, typename... targs>
	struct ifunction 
	{
		virtual treturn invoke(const targs&... args) const = 0;

		virtual treturn operator () (const targs&... args) const
		{
			invoke(std::forward<const targs&>(args)...);
		}
	};

	template<typename treturn, typename... targs>
	class function_ptr : public ifunction<treturn, targs...>
	{
	private:
		treturn(*_value)(const targs&...) = nullptr;
	public:
		function_ptr(treturn(*value)(const targs&...)) : _value(value) { }

		treturn invoke(const targs&... args) const override
		{
			return (*_value)(std::forward<const targs&>(args)...);
		}
	};

	template<typename tclass, typename treturn, typename... targs>
	class method_ptr : public ifunction<treturn, targs...> 
	{
	private:
		tclass* _class_instance = nullptr;
		treturn(tclass::*_value)(const targs&...) = nullptr;
	public:
		method_ptr(tclass* class_instance, treturn(tclass::*value)(const targs&...))
			: _class_instance(class_instance), _value(value) { }

		treturn invoke(const targs&... args) const override
		{
			return ((*_class_instance).*_value)(std::forward<const targs&>(args)...);
		}
	};

	template<typename treturn, typename... targs>
	class lambda : public ifunction<treturn, targs...> 
	{
	private:
		std::function<treturn(const targs&...)> _value;
	public:
		lambda(const std::function<treturn(const targs&...)>& value) : _value(value) { }

		treturn invoke(const targs&... args) const override
		{
			return _value(std::forward<const targs&>(args)...);
		}
	};

	template<typename... targs>
	class action : public ifunction<void, targs...>
	{
	private:
		std::vector<ifunction<void, targs...>*> _functions;
	public:
		action() = default;

		action(ifunction<void, targs...>* function) 
		{
			_functions.push_back(function);
		}

		~action() 
		{
			for (auto function : _functions) 
			{
				delete function;
				function = nullptr;
			}
			_functions.clear();
		}

		void assign(ifunction<void, targs...>* function) 
		{
			_functions.assign(function);
		}

		void operator = (ifunction<void, targs...>* function) 
		{
			assign(function);
		}

		void add(ifunction<void, targs...>* function) 
		{
			_functions.push_back(function);
		}

		void operator += (ifunction<void, targs...>* function) 
		{
			add(function);
		}

		void remove(ifunction<void, targs...>* function) 
		{
			auto it = std::find(_functions.begin(), _functions.end(), function);
			if (it != _functions.end())
			{
				_functions.erase(it);
				delete function;
				function = nullptr;
			}
		}

		void operator -= (ifunction<void, targs...>* function) 
		{
			remove(function);
		}

		void invoke(const targs&... args) const override 
		{
			for (auto function : _functions)
				function->invoke(std::forward<const targs&>(args)...);
		}
	};
}