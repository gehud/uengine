#pragma once

#include "uengine/rendering/index_buffer.h"

namespace ue 
{
	class opengl_index_buffer : public index_buffer 
	{
	private:
		unsigned int _id;
		int _count;
		int _stride;
		int _type;
	public:
		opengl_index_buffer(const unsigned char* indices, int count, int stride);
		opengl_index_buffer(const unsigned short* indices, int count, int stride);
		opengl_index_buffer(const unsigned int* indices, int count, int stride);

		~opengl_index_buffer();

		int get_count() const override { return _count; }

		int get_stride() const override { return _stride; }

		int get_type() const override { return _type; }

		void bind() const override;
		void unbind() const override;

	};
}