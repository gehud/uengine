#pragma once

#include "uengine/core/layer.h"

namespace ue 
{
	class gui_layer : public layer 
	{
	public:
		void on_attach() override;
		void on_detach() override;

		void begin();
		void end();
	};
}