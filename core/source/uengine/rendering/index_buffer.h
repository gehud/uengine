#pragma once

#include <memory>

namespace ue 
{
	class index_buffer 
	{
	public:
		static std::shared_ptr<index_buffer> create(const unsigned char* indices, int count, int stride);
		static std::shared_ptr<index_buffer> create(const unsigned short* indices, int count, int stride);
		static std::shared_ptr<index_buffer> create(const unsigned int* indices, int count, int stride);

		virtual int get_count() const = 0;

		virtual int get_stride() const = 0;

		virtual int get_type() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}