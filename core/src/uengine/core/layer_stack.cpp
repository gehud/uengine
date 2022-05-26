#include "layer_stack.h"

namespace ue 
{
	layer_stack::~layer_stack()
	{
		for (auto layer : _layers) 
		{
			layer->on_detach();
			delete layer;
			layer = nullptr;
		}
	}

	void layer_stack::push_layer(layer* layer)
	{
		layer->on_attach();
		_layers.emplace(_layers.begin() + _insert_index, layer);
		_insert_index++;
	}

	void layer_stack::pop_layer(layer* layer)
	{
		auto it = std::find(_layers.begin(), _layers.begin() + _insert_index, layer);
		if (it != _layers.begin() + _insert_index)
		{
			layer->on_detach();
			_layers.erase(it);
			_insert_index--;
		}
	}

	void layer_stack::push_overlay(layer* overlay)
	{
		overlay->on_attach();
		_layers.emplace_back(overlay);
	}

	void layer_stack::pop_overlay(layer* overlay)
	{
		auto it = std::find(_layers.begin() + _insert_index, _layers.end(), overlay);
		if (it != _layers.end())
		{
			overlay->on_detach();
			_layers.erase(it);
		}
	}
}