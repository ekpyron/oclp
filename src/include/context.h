/*  
 * This file is part of clp.
 *
 * clp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * clp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with clp.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CLP_CONTEXT_H
#define CLP_CONTEXT_H

#include "common.h"
#include "memory.h"
#include <glp/glp.h>

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
	 CommandQueue CreateCommandQueue (cl_command_queue_properties properties);
	 Program CreateProgramWithSource (const std::string &strings);
	 void GetDeviceInfo (cl_device_info param_name, size_t param_value_size,
											 void *param_value, size_t *param_value_size_ret);
private:
	 cl_context context;
	 cl_device_id deviceid;
};

} /* namespace cl */

#endif /* CLP_CONTEXT_H */
