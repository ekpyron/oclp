/*  
 * This file is part of oclp.
 *
 * oclp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * oclp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with oclp.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef OCLP_CONTEXT_H
#define OCLP_CONTEXT_H

#include "common.h"
#include "memory.h"
#include <oglp/oglp.h>

namespace cl {

class Context
{
public:
	 Context (void);
	 Context (const Context &c);
	 Context (Context &&c);
	 ~Context (void);
	 Context &operator= (const Context &c);
	 Context &operator= (Context &&c);
	 Memory CreateBuffer (cl_mem_flags flags, size_t size, void *ptr);
	 Memory CreateImage2D (cl_mem_flags flags,
												 cl_channel_order image_channel_order,
												 cl_channel_type image_channel_data_type,
												 size_t image_width, size_t image_height,
												 size_t image_row_pitch, void *ptr);
	 Memory CreateFromGLBuffer (cl_mem_flags flags, const gl::Buffer &buffer);
	 Memory CreateFromGLTexture2D (cl_mem_flags flags, GLenum texture_target,
																 GLint miplevel, const gl::Texture &texture);
	 Memory CreateFromGLTexture3D (cl_mem_flags flags, GLenum texture_target,
																 GLint miplevel, const gl::Texture &texture);
	 Memory CreateFromGLRenderbuffer (cl_mem_flags flags,
																		const gl::Renderbuffer &renderbuffer);
	 Memory CreateFromGLRenderbuffer (cl_mem_flags flags,
																		GLuint renderbuffer);
	 CommandQueue CreateCommandQueue (cl_command_queue_properties properties);
	 Program CreateProgramWithSource (const std::string &strings);
	 void GetDeviceInfo (cl_device_info param_name, size_t param_value_size,
											 void *param_value, size_t *param_value_size_ret);
	 bool IsExtensionSupported (const std::string &extension);
#ifdef OCLP_ENABLE_CL_KHR_GL_EVENT
	 cl_event CreateEventFromGLsync (GLsync sync);
#endif /* OCLP_ENABLE_CL_KHR_GL_EVENT */
	 cl_event CreateUserEvent (void);
private:
	 cl_context context;
	 cl_device_id deviceid;
};

} /* namespace cl */

#endif /* OCLP_CONTEXT_H */
