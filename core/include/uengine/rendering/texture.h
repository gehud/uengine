#pragma once

namespace ue 
{
	enum class texture_format 
	{
		rgb8,
		rgb16,
		rgb32,
		rgba8,
		rgba16,
		rgba32
	};

	enum class texture_wrap_mode 
	{
		repeat,
		mirror,
		clamp,
	};

	enum class texture_filter_mode 
	{
		nearest,
		linear
	};

	class texture 
	{
	public:
		virtual int get_width() const = 0;
		virtual int get_height() const = 0;

		virtual texture_wrap_mode get_wrap_mode() const = 0;
		virtual void set_wrap_mode(texture_wrap_mode value) = 0;

		virtual texture_filter_mode get_filter_mode() const = 0;
		virtual void set_filter_mode(texture_filter_mode value) = 0;

		virtual void bind(int slot = 0) const = 0;
	};
}