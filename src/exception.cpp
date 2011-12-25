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
#include "clp.h"
#include <sstream>

namespace cl {

Exception::Exception (const char *m, cl_int err) : msg (m), error (err)
{
}

const char *Exception::what (void) const throw ()
{
	std::stringstream stream;
	stream << msg << ": ";
	switch (error)
	{
	case CL_SUCCESS:
		stream << "success";
		break;
	case CL_DEVICE_NOT_FOUND:
		stream << "device not found";
		break;
	case CL_DEVICE_NOT_AVAILABLE:
		stream << "device not available";
		break;
	case CL_COMPILER_NOT_AVAILABLE:
		stream << "compiler not available";
		break;
	case CL_MEM_OBJECT_ALLOCATION_FAILURE:
		stream << "mem object allocation failure";
		break;
	case CL_OUT_OF_RESOURCES:
		stream << "out of resources";
		break;
	case CL_OUT_OF_HOST_MEMORY:
		stream << "out of host memory";
		break;
	case CL_PROFILING_INFO_NOT_AVAILABLE:
		stream << "profiling info not avaible";
		break;
	case CL_MEM_COPY_OVERLAP:
		stream << "mem copy overlap";
		break;
	case CL_IMAGE_FORMAT_MISMATCH:
		stream << "image format mismatch";
		break;
	case CL_IMAGE_FORMAT_NOT_SUPPORTED:
		stream << "image format not supported";
		break;
	case CL_BUILD_PROGRAM_FAILURE:
		stream << "build program failure";
		break;
	case CL_MAP_FAILURE:
		stream << "map failure";
		break;
	case CL_MISALIGNED_SUB_BUFFER_OFFSET:
		stream << "misaligned sub buffer offset";
		break;
	case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
		stream << "exec status error for events in wait list";
		break;
	case CL_INVALID_VALUE:
		stream << "invalid value";
		break;
	case CL_INVALID_DEVICE_TYPE:
		stream << "invalid device type";
		break;
	case CL_INVALID_PLATFORM:
		stream << "invalid platform";
		break;
	case CL_INVALID_DEVICE:
		stream << "invalid device";
		break;
	case CL_INVALID_CONTEXT:
		stream << "invalid context";
		break;
	case CL_INVALID_QUEUE_PROPERTIES:
		stream << "invalid queue properties";
		break;
	case CL_INVALID_COMMAND_QUEUE:
		stream << "invalid command queue";
		break;
	case CL_INVALID_HOST_PTR:
		stream << "invalid host ptr";
		break;
	case CL_INVALID_MEM_OBJECT:
		stream << "invalid mem object";
		break;
	case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
		stream << "invalid image format descriptor";
		break;
	case CL_INVALID_IMAGE_SIZE:
		stream << "invalid image size";
		break;
	case CL_INVALID_SAMPLER:
		stream << "invalid sampler";
		break;
	case CL_INVALID_BINARY:
		stream << "invalid binary";
		break;
	case CL_INVALID_BUILD_OPTIONS:
		stream << "invalid build options";
		break;
	case CL_INVALID_PROGRAM:
		stream << "invalid program";
		break;
	case CL_INVALID_PROGRAM_EXECUTABLE:
		stream << "invalid program executable";
		break;
	case CL_INVALID_KERNEL_NAME:
		stream << "invalid kernel name";
		break;
	case CL_INVALID_KERNEL_DEFINITION:
		stream << "invalid kernel definition";
		break;
	case CL_INVALID_KERNEL:
		stream << "invalid kernel";
		break;
	case CL_INVALID_ARG_INDEX:
		stream << "invalid arg index";
		break;
	case CL_INVALID_ARG_VALUE:
		stream << "invalid arg value";
		break;
	case CL_INVALID_KERNEL_ARGS:
		stream << "invalid kernel args";
		break;
	case CL_INVALID_WORK_DIMENSION:
		stream << "invalid work dimension";
		break;
	case CL_INVALID_WORK_GROUP_SIZE:
		stream << "invalid work group size";
		break;
	case CL_INVALID_WORK_ITEM_SIZE:
		stream << "invalid work item size";
		break;
	case CL_INVALID_GLOBAL_OFFSET:
		stream << "invalid global offset";
		break;
	case CL_INVALID_EVENT_WAIT_LIST:
		stream << "invalid event wait list";
		break;
	case CL_INVALID_EVENT:
		stream << "invalid event";
		break;
	case CL_INVALID_OPERATION:
		stream << "invalid operation";
		break;
	case CL_INVALID_GL_OBJECT:
		stream << "invalid gl object";
		break;
	case CL_INVALID_BUFFER_SIZE:
		stream << "invalid buffer size";
		break;
	case CL_INVALID_MIP_LEVEL:
		stream << "invalid mip level";
		break;
	case CL_INVALID_GLOBAL_WORK_SIZE:
		stream << "invalid global work size";
		break;
	case CL_INVALID_PROPERTY:
		stream << "invalid property";
		break;
	case CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR:
		stream << "invalid gl sharegroup reference";
		break;
	case CL_PLATFORM_NOT_FOUND_KHR:
		stream << "platform not found";
		break;
	default:
		stream << error;
	}
	return stream.str ().c_str ();
}

} /* namespace cl */
