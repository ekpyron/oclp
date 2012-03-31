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
#include "oclp.h"
#include <iostream>

#if defined (__APPLE__) || defined (MACOSX)
// TODO
#elif defined WIN32 || defined _WIN32
#include <windows.h>
#else
#include <GL/glx.h>
#endif

namespace cl {

void CL_CALLBACK pfn_notify (const char *errinfo,
														 const void *private_info,
														 size_t cb,
														 void *user_data)
{
	std::cerr << "OpenCL error: " << errinfo << std::endl;
}

Context::Context (void) : context (NULL)
{
	cl_int err;
#if defined (__APPLE__) || defined (MACOSX)
// TODO
#elif defined WiN32 || defined _WIN32
	cl_context_properties props[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties) wglGetCurrentContext (),
		CL_WGL_HDC_KHR, (cl_context_properties) wglGetCurrentDC (),
		0
	};
#else
	cl_context_properties props[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties) glXGetCurrentContext (),
		CL_GLX_DISPLAY_KHR, (cl_context_properties) glXGetCurrentDisplay (),
		0
	};
#endif
	cl_uint num_platforms;
	std::vector<cl_platform_id> platforms;

	err = clGetPlatformIDs (0, NULL, &num_platforms);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot obtain the number of OpenCL platform IDs.", err);

	platforms.resize (num_platforms);

	err = clGetPlatformIDs (platforms.size (), &platforms[0], &num_platforms);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot obtain the available OpenCL platform IDs.", err);

	for (cl_platform_id &platform : platforms)
	{
		std::vector<cl_device_id> devices;
		cl_uint num_devices;

		{
			std::vector<char> buffer;
			size_t len;
			err = clGetPlatformInfo (platform, CL_PLATFORM_NAME, 0, NULL, &len);
			if (err == CL_SUCCESS)
			{
				buffer.resize (len + 1);
				err = clGetPlatformInfo (platform, CL_PLATFORM_NAME, len, &buffer[0], NULL);
				if (err == CL_SUCCESS)
				{
					buffer[len] = 0;
					std::cerr << "CL_PLATFORM_NAME: " << &buffer[0] << std::endl;
				}
			}
			err = clGetPlatformInfo (platform, CL_PLATFORM_VENDOR, 0, NULL, &len);
			if (err == CL_SUCCESS)
			{
				buffer.resize (len + 1);
				err = clGetPlatformInfo (platform, CL_PLATFORM_VENDOR, len, &buffer[0], NULL);
				if (err == CL_SUCCESS)
				{
					buffer[len] = 0;
					std::cerr << "CL_PLATFORM_VENDOR: " << &buffer[0] << std::endl;
				}
			}
		}

		err = clGetDeviceIDs (platform, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
		if (err != CL_SUCCESS)
			 continue;
		devices.resize (num_devices);
		err = clGetDeviceIDs (platform, CL_DEVICE_TYPE_ALL, devices.size (),
													&devices[0], &num_devices);
		if (err != CL_SUCCESS)
			 continue;

		for (cl_device_id &device : devices)
		{
			{
				std::vector<char> buffer;
				size_t len;
				err = clGetDeviceInfo (device, CL_DEVICE_NAME, 0, NULL, &len);
				if (err == CL_SUCCESS)
				{
					buffer.resize (len + 1);
					err = clGetDeviceInfo (device, CL_DEVICE_NAME, len, &buffer[0], NULL);
					buffer[len] = 0;
					if (err == CL_SUCCESS)
					{
						std::cerr << "CL_DEVICE_NAME: " << &buffer[0] << std::endl;
					}
				}
			}

			context = clCreateContext (props, 1, &device, pfn_notify,
																 NULL, &err);
			if (err == CL_SUCCESS)
			{
				deviceid = device;
				break;
			}
		}
	}

	if (context == NULL)
		 throw Exception ("Cannot create a suitable OpenCL context.", err);
}

Context::~Context (void)
{
	if (context != NULL)
	{
		clReleaseContext (context);
		context = NULL;
	}
}

Memory Context::CreateBuffer (cl_mem_flags flags, size_t size, void *ptr)
{
	cl_mem mem;
	cl_int err;
	mem = clCreateBuffer (context, flags, size, ptr, &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create OpenCL memory"
											" from a memory buffer.", err);
	return Memory (mem);
}

Memory Context::CreateImage2D (cl_mem_flags flags,
															 cl_channel_order image_channel_order,
															 cl_channel_type image_channel_data_type,
															 size_t image_width, size_t image_height,
															 size_t image_row_pitch, void *ptr)
{
	cl_mem mem;
	cl_int err;
	const cl_image_format format = { image_channel_order,
																	 image_channel_data_type };
	mem = clCreateImage2D (context, flags, &format, image_width, image_height,
												 image_row_pitch, ptr, &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create an OpenCL image.", err);
	return Memory (mem);
}

Memory Context::CreateFromGLBuffer (cl_mem_flags flags,
																		const gl::Buffer &buffer)
{
	cl_mem mem;
	cl_int err;
	mem = clCreateFromGLBuffer (context, flags, buffer.get (), &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create OpenCL memory from OpenGL buffer.", err);
	return Memory (mem);
}

Memory Context::CreateFromGLTexture2D (cl_mem_flags flags,
																			 GLenum textarget,
																			 GLint miplevel,
																			 const gl::Texture &texture)
{
	cl_mem mem;
	cl_int err;
	mem = clCreateFromGLTexture2D (context, flags, textarget, miplevel,
																 texture.get (), &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create OpenCL memory from OpenGL texture", err);
	return Memory (mem);
}

Memory Context::CreateFromGLTexture3D (cl_mem_flags flags,
																			 GLenum textarget,
																			 GLint miplevel,
																			 const gl::Texture &texture)
{
	cl_mem mem;
	cl_int err;
	mem = clCreateFromGLTexture3D (context, flags, textarget, miplevel,
																 texture.get (), &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create OpenCL memory from OpenGL texture", err);
	return Memory (mem);
}

Memory Context::CreateFromGLRenderbuffer (cl_mem_flags flags,
																					const gl::Renderbuffer &renderbuffer)
{
	cl_mem mem;
	cl_int err;
	mem = clCreateFromGLRenderbuffer (context, flags, renderbuffer.get (), &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create OpenCL memory from OpenGL renderbuffer",
											err);
	return Memory (mem);
}

Memory Context::CreateFromGLRenderbuffer (cl_mem_flags flags,
																					GLuint renderbuffer)
{
	cl_mem mem;
	cl_int err;
	std::cerr << "Create OpenCL memory from OpenGL renderbuffer." << std::endl;
	mem = clCreateFromGLRenderbuffer (context, flags, renderbuffer, &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create OpenCL memory from OpenGL renderbuffer",
											err);
	return Memory (mem);
}

Program Context::CreateProgramWithSource (const std::string &src)
{
	cl_program program;
	cl_int err;
	const char *source = src.c_str ();
	program = clCreateProgramWithSource (context, 1, &source, NULL, &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create an OpenCL program with source.", err);
	return Program (program);
}

CommandQueue Context::CreateCommandQueue (cl_command_queue_properties properties)
{
	cl_command_queue queue;
	cl_int err;
	queue = clCreateCommandQueue (context, deviceid, properties, &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create an OpenCL command queue.", err);
	return CommandQueue (queue);
}

void Context::GetDeviceInfo (cl_device_info param_name,
														 size_t param_value_size,
														 void *param_value,
														 size_t *param_value_size_ret)
{
	cl_int err;
	err = clGetDeviceInfo (deviceid, param_name, param_value_size,
												 param_value, param_value_size_ret);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot obtain OpenCL device information", err);
}

#ifdef OCLP_ENABLE_CL_KHR_GL_EVENT
cl_event Context::CreateEventFromGLsync (GLsync sync)
{
	cl_int err;
	cl_event event;
	event = clCreateEventFromGLsyncKHR (context, sync, &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create an OpenCL event from an OpenGL "
											"sync object", err);
	return event;
}
#endif /* OCLP_ENABLE_CL_KHR_GL_EVENT */

cl_event Context::CreateUserEvent (void)
{
	cl_int err;
	cl_event event;
	event = clCreateUserEvent (context, &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create an OpenCL user event", err);
	return event;
}

} /* namespace cl */
