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
#ifndef CLP_COMMANDQUEUE_H
#define CLP_COMMANDQUEUE_H

#include "common.h"
#include "memory.h"

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
private:
	 CommandQueue (cl_command_queue q);
	 friend class Context;
	 cl_command_queue queue;
};

} /* namespace cl */

#endif /* CLP_COMMANDQUEUE_H */