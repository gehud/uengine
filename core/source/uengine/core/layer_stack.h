#pragma once

#include "uengine/core/layer.h"

#include <vector>

namespace ue 
{
	class layer_stack 
	{
	private:
		std::vector<layer*> _layers;
		unsigned int _insert_index = 0;
	public:
		~layer_stack();

		void push_layer(layer* layer);
		void pop_layer(layer* layer);

		void push_overlay(layer* overlay);
		void pop_overlay(layer* overlay);

		std::vector<layer*>::iterator begin() { return _layers.begin(); }
		std::vector<layer*>::iterator end() { return _layers.end(); }
	};
}