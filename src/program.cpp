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

namespace cl {

Program::Program (void) : program (NULL)
{
}

Program::Program (cl_program p) : program (p)
{
}

Program::Program (Program &&p) : program (p.program)
{
	p.program = NULL;
}

Program::~Program (void)
{
	if (program)
	{
		clReleaseProgram (program);
		program = NULL;
	}
}

Program &Program::operator= (Program &&p)
{
	program = p.program;
	p.program = NULL;
}

void Program::UnloadCompiler (void)
{
	clUnloadCompiler ();
}

void Program::Build (const std::string &options)
{
	cl_int err;
	err = clBuildProgram (program, 0, NULL, options.c_str (), NULL, NULL);
	if (err != CL_SUCCESS)
	{
		cl_int num_devices;
		std::vector<cl_device_id> devices;
		err = clGetProgramInfo (program, CL_PROGRAM_NUM_DEVICES, sizeof (cl_int),
														&num_devices, NULL);
		if (err != CL_SUCCESS)
		{
			 throw Exception ("Cannot build an OpenCL program and "
												"cannot query devices", err);
		}
		devices.resize (num_devices);
		err = clGetProgramInfo (program, CL_PROGRAM_DEVICES,
														sizeof (cl_device_id) * devices.size (),
														&devices[0], NULL);
		if (err != CL_SUCCESS)
		{
			 throw Exception ("Cannot build an OpenCL program and "
												"cannot query devices", err);
		}
		for (cl_device_id &dev : devices)
		{
			cl_build_status status;
			cl_int err;
			std::vector<char> log;
			size_t size;
			err = clGetProgramBuildInfo (program, dev, CL_PROGRAM_BUILD_STATUS,
																	 sizeof (cl_build_status), &status, NULL);
			if (err != CL_SUCCESS)
				 continue;
			if (status != CL_BUILD_ERROR)
				 continue;
			err = clGetProgramBuildInfo (program, dev, CL_PROGRAM_BUILD_LOG,
																	 0, NULL, &size);
			if (err != CL_SUCCESS)
				 continue;
			log.resize (size);
			err = clGetProgramBuildInfo (program, dev, CL_PROGRAM_BUILD_LOG,
																	 size, &log[0], NULL);
			if (err != CL_SUCCESS)
				 continue;
			std::cerr << "Build log:" << std::endl
								<< &log[0] << std::endl;
			
		}
		throw Exception ("Cannot build an OpenCL program", err);
	}
}

Kernel Program::CreateKernel (const char *kernel_name)
{
	cl_kernel kernel;
	cl_int err;
	kernel = clCreateKernel (program, kernel_name, &err);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot create an OpenCL kernel.", err);
	return Kernel (kernel);
}

} /* namespace cl */
