#pragma once

namespace ue 
{
	class texture 
	{
	public:
		virtual int get_width() const = 0;
		virtual int get_height() const = 0;

		virtual void bind(int slot = 0) const = 0;
	};
}