#pragma once

#include "uengine/core/assertion.h"
#include "uengine/core/window.h"
#include "uengine/core/layer_stack.h"
#include "uengine/core/scene.h"
#include "uengine/core/system.h"
#include "uengine/core/application_platform.h"
#include "uengine/gui/gui_layer.h"

namespace ue 
{
	class application 
	{
	private:
		static application* _instance;
		static application_platform _platform;
		bool _is_runing;
		window* _window;
		layer_stack _layers_stack;
		gui_layer* _gui_layer;
		std::vector<scene*> _scenes;
		scene* _current_scene = nullptr;
		std::vector<system*> _systems;
	public:
		application();

		~application();

		static application& get_instance() { return *_instance; }

		static application_platform get_platform() { return _platform; }

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
			UE_CORE_ASSERT(_current_scene != nullptr, "Missing scene.");
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