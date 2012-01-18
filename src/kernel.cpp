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
#include <stdexcept>

#if defined (__APPLE__) || defined (MACOSX)
// TODO
#elif defined WIN32 || defined _WIN32
#include <windows.h>
#else
#include <GL/glx.h>
#endif

namespace cl {

Kernel::Kernel (void) : kernel (NULL)
{
}

Kernel::Kernel (cl_kernel k) : kernel (k)
{
}

Kernel::Kernel (Kernel &&k) : kernel (k.kernel)
{
	k.kernel = NULL;
}

Kernel::~Kernel (void)
{
	if (kernel != NULL)
	{
		clReleaseKernel (kernel);
		kernel = NULL;
	}
}

Kernel &Kernel::operator= (Kernel &&k)
{
	kernel = k.kernel;
	k.kernel = NULL;
}

void Kernel::SetArg (cl_uint arg_index, size_t arg_size,
										 const void *arg_value)
{
	cl_int err;
	err = clSetKernelArg (kernel, arg_index, arg_size, arg_value);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot set an OpenCL kernel argument.", err);
}

void Kernel::SetArg (cl_uint arg_index, const Memory &memory)
{
	cl_int err;
	cl_mem mem;
	mem = memory.get ();
	err = clSetKernelArg (kernel, arg_index, sizeof (cl_mem), &mem);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot set an OpenCL kernel argument.", err);
}

cl_kernel Kernel::get (void) const
{
	return kernel;
}

} /* namespace cl */
