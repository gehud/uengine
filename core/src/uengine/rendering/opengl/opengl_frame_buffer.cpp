#include "opengl_frame_buffer.h"

#include "uengine/core/assertion.h"

#include <glad/glad.h>

namespace ue 
{
	opengl_frame_buffer::opengl_frame_buffer(const frame_buffer_descriptor& descriptor)
		: _descriptor(descriptor) 
	{
		glCreateFramebuffers(1, &_id);
		glBindFramebuffer(GL_FRAMEBUFFER, _id);

		glCreateTextures(GL_TEXTURE_2D, 1, &_color_buffer_id);
		glBindTexture(GL_TEXTURE_2D, _color_buffer_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _descriptor.width, _descriptor.height, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _color_buffer_id, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &_depth_buffer_id);
		glBindTexture(GL_TEXTURE_2D, _depth_buffer_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _descriptor.width, _descriptor.height, 0, GL_DEPTH_STENCIL,
			GL_UNSIGNED_INT_24_8, NULL);

		UE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete.");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	opengl_frame_buffer::~opengl_frame_buffer()
	{
		glDeleteFramebuffers(1, &_id);
	}

	void opengl_frame_buffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _id);
	}

	void opengl_frame_buffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}