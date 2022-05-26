#pragma once

namespace ue 
{
	class component 
	{
		friend class entity;
	private:
		entity* _entity = nullptr;
	public:
		component() = default;
		component(entity& entity) : _entity(&entity) { }

		~component() { _entity = nullptr; }

		entity& get_entity() { return *_entity; }
	};
}