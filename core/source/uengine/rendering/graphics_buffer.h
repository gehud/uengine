#pragma once

#include "uengine/core/types.h"
#include "uengine/core/assertion.h"

#include <glad/glad.h>

namespace ue {
	class graphics_buffer {
	public:
		enum class target {
			vertex,
			index,
		};

		graphics_buffer(target target, uint32 count, uint32 stride) 
			: _target(target), _count(count), _stride(stride) {
			glGenBuffers(1, &_id);
		}

		~graphics_buffer() {
			glDeleteBuffers(1, &_id);
		}

		target get_target() const { return _target; }
		uint32 get_count() const { return _count; }
		uint32 get_stride() const { return _stride; }

		void set_data(const void* value) {
			switch (_target) {
				case target::vertex: {
					glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(_count * _stride), value, GL_STATIC_DRAW);
					return;
				}
				case target::index: {
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(_count * _stride), value, GL_STATIC_DRAW);
					return;
				}
			}

			UE_CORE_ASSERT(false, "Unknown graphics buffer target.");
		}

		void bind() const {
			switch (_target) {
				case target::vertex: {
					glBindBuffer(GL_ARRAY_BUFFER, _id);
					return;
				}
				case target::index: {
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
					return;
				}
			}

			UE_CORE_ASSERT(false, "Unknown graphics buffer target.");
		}

		void unbind() const {
			switch (_target) {
				case target::vertex: {
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					return;
				}
				case target::index: {
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
					return;
				}
			}

			UE_CORE_ASSERT(false, "Unknown graphics buffer target.");
		}
	private:
		uint32 _id;
		target _target;
		uint32 _count;
		uint32 _stride;
	};
}