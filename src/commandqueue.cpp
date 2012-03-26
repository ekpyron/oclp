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

namespace cl {

CommandQueue::CommandQueue (void) : queue (NULL)
{
}

CommandQueue::CommandQueue (cl_command_queue cq) : queue (cq)
{
}

CommandQueue::CommandQueue (const CommandQueue &cq) : queue (cq.queue)
{
	if (queue)
	{
		clRetainCommandQueue (queue);
	}
}

CommandQueue::CommandQueue (CommandQueue &&cq) : queue (cq.queue)
{
	cq.queue = NULL;
}

CommandQueue::~CommandQueue (void)
{
	if (queue != NULL)
	{
		clReleaseCommandQueue (queue);
		queue = NULL;
	}
}

CommandQueue &CommandQueue::operator= (CommandQueue &&cq)
{
	queue = cq.queue;
	cq.queue = NULL;
}

CommandQueue &CommandQueue::operator= (const CommandQueue &cq)
{
	queue = cq.queue;
	if (queue)
	{
		clRetainCommandQueue (queue);
	}
}

void CommandQueue::Flush (void)
{
	cl_int err;
	err = clFlush (queue);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot flush an OpenCL command queue.", err);
}

void CommandQueue::Finish (void)
{
	cl_int err;
	err = clFinish (queue);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot finish an OpenCL command queue.", err);
}

void CommandQueue::EnqueueNDRangeKernel (const Kernel &kernel,
																				 cl_uint work_dim,
																				 const size_t *global_work_offset,
																				 const size_t *global_work_size,
																				 const size_t *local_work_size,
																				 cl_uint num_events_in_wait_list,
																				 const cl_event *event_wait_list,
																				 cl_event *event)
{
	cl_int err;
	err = clEnqueueNDRangeKernel (queue, kernel.get (), work_dim,
																global_work_offset, global_work_size,
																local_work_size, num_events_in_wait_list,
																event_wait_list, event);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot enqueue an OpenCL kernel.", err);
}

void CommandQueue::EnqueueAcquireGLObjects (std::vector<Memory> objects,
																						cl_uint num_events_in_wait_list,
																						const cl_event *event_wait_list,
																						cl_event *event)
{
	cl_int err;
	std::vector<cl_mem> objs;
	for (Memory &mem : objects)
	{
		objs.push_back (mem.get ());
	}
	err = clEnqueueAcquireGLObjects (queue, objs.size (), &objs[0],
																	 num_events_in_wait_list,
																	 event_wait_list, event);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot enqueue an OpenGL object acquisition to "
											"an OpenCL command queue.", err);
}

void CommandQueue::EnqueueReleaseGLObjects (std::vector<Memory> objects,
																						cl_uint num_events_in_wait_list,
																						const cl_event *event_wait_list,
																						cl_event *event)
{
	cl_int err;
	std::vector<cl_mem> objs;
	for (Memory &mem : objects)
	{
		objs.push_back (mem.get ());
	}
	err = clEnqueueReleaseGLObjects (queue, objs.size (), &objs[0],
																	 num_events_in_wait_list,
																	 event_wait_list, event);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot enqueue an OpenGL object release to "
											"an OpenCL command queue.", err);
}

void CommandQueue::EnqueueCopyBufferToImage (const Memory &src,
																						 const Memory &dst,
																						 size_t src_offset,
																						 const size_t *dst_origin,
																						 const size_t *region,
																						 cl_uint num_events_in_wait_list,
																						 const cl_event *event_wait_list,
																						 cl_event *event)
{
	cl_int err;

	err = clEnqueueCopyBufferToImage (queue, src.get (), dst.get (),
																		src_offset, dst_origin, region,
																		num_events_in_wait_list, event_wait_list,
																		event);

	if (err != CL_SUCCESS)
		 throw Exception ("Cannot enqueue a copy operation from a bufer to"
											" an image.", err);
}

void CommandQueue::EnqueueWriteBuffer (const Memory &buffer,
																			 cl_bool blocking_write, size_t offset,
																			 size_t cb, const void *ptr,
																			 cl_uint num_events_in_wait_list,
																			 const cl_event *event_wait_list,
																			 cl_event *event)
{
	cl_int err;
	err = clEnqueueWriteBuffer (queue, buffer.get (), blocking_write,
															offset, cb, ptr, num_events_in_wait_list,
															event_wait_list, event);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot enqueue a buffer write operation", err);
}

void CommandQueue::EnqueueReadBuffer (const Memory &buffer,
																			cl_bool blocking_read, size_t offset,
																			size_t cb, void *ptr,
																			cl_uint num_events_in_wait_list,
																			const cl_event *event_wait_list,
																			cl_event *event)
{
	cl_int err;
	err = clEnqueueReadBuffer (queue, buffer.get (), blocking_read,
															offset, cb, ptr, num_events_in_wait_list,
															event_wait_list, event);
	if (err != CL_SUCCESS)
		 throw Exception ("Cannot enqueue a buffer read operation", err);
}

} /* namespace cl */
