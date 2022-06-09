#pragma once

namespace ue 
{
	class component
	{
		friend class entity;
	private:
		const entity* _entity = nullptr;
	public:
		component(const entity& entity) : _entity(&entity) { }

		~component() { _entity = nullptr; }

		const entity& get_entity() { return *_entity; }
	};
}