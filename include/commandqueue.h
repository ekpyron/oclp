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
#ifndef OCLP_COMMANDQUEUE_H
#define OCLP_COMMANDQUEUE_H

#include "common.h"
#include "memory.h"
#include <glm/glm.hpp>

namespace cl {

class CommandQueue
{
public:
	 CommandQueue (void);
	 CommandQueue (const CommandQueue &cq);
	 CommandQueue (CommandQueue &&cq);
	 ~CommandQueue (void);
	 CommandQueue &operator= (const CommandQueue &cq);
	 CommandQueue &operator= (CommandQueue &&cq);
	 void Flush (void);
	 void Finish (void);
	 void EnqueueNDRangeKernel (const Kernel &kernel, cl_uint work_dim,
															const size_t *global_work_offset,
															const size_t *global_work_size,
															const size_t *local_work_size,
															cl_uint num_events_in_wait_list,
															const cl_event *event_wait_list,
															cl_event *event);
	 void EnqueueAcquireGLObjects (std::vector<Memory> objs,
																 cl_uint num_events_in_wait_list,
																 const cl_event *event_wait_list,
																 cl_event *event);
	 void EnqueueReleaseGLObjects (std::vector<Memory> objs,
																 cl_uint num_events_in_wait_list,
																 const cl_event *event_wait_list,
																 cl_event *event);
	 void EnqueueCopyBufferToImage (const Memory &src,
																	const Memory &dst,
																	size_t src_offset,
																	const size_t *dst_origin,
																	const size_t *region,
																	cl_uint num_events_in_wait_list,
																	const cl_event *event_wait_list,
																	cl_event *event);
	 void EnqueueWriteBuffer (const Memory &buffer, cl_bool blocking_write,
														size_t offset, size_t cb, const void *ptr,
														cl_uint num_events_in_wait_list,
														const cl_event *event_wait_list, cl_event *event);
	 void EnqueueReadBuffer (const Memory &buffer, cl_bool blocking_write,
													 size_t offset, size_t cb, void *ptr,
													 cl_uint num_events_in_wait_list,
													 const cl_event *event_wait_list, cl_event *event);
	 cl_event EnqueueMarker (void);
private:
	 CommandQueue (cl_command_queue q);
	 friend class Context;
	 cl_command_queue queue;
};

} /* namespace cl */

#endif /* OCLP_COMMANDQUEUE_H */
