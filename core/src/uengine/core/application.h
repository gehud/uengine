#pragma once

#include "uengine/core/window.h"
#include "uengine/core/layer_stack.h"
#include "uengine/core/scene.h"
#include "uengine/core/system.h"
#include "uengine/imgui/imgui_layer.h"

namespace ue 
{
	class application 
	{
	private:
		static application* _instance;
		bool _is_runing;
		window* _window;
		layer_stack _layers_stack;
		imgui_layer* _imgui_layer;
		std::vector<scene*> _scenes;
		scene* _current_scene = nullptr;
		std::vector<system*> _systems;
	public:
		application();

		~application();

		static application& get_instance() { return *_instance; }

		window& get_window() { return *_window; }

		void push_layer(layer* layer) { _layers_stack.push_layer(layer); }
		void push_overlay(layer* overlay) { _layers_stack.push_overlay(overlay); }

		void add_scene(scene& scene) 
		{ 
			_scenes.push_back(&scene); 
			_current_scene = &scene;
		}

		template<typename t, typename std::enable_if<std::is_base_of<system, t>::value, bool>::type = true>
		void add_system() 
		{
			t* s = new t();
			s->_registry = &_current_scene->_registry;
			_systems.push_back(s);
		}

		void run();

		virtual void on_update() { }

		virtual void on_gui() { }

		void close();
	};
}