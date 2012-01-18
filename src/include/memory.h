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
#ifndef OCLP_MEMORY_H
#define OCLP_MEMORY_H

#include "common.h"

namespace cl {

class Memory
{
public:
	 Memory (void);
	 Memory (const Memory &m);
	 Memory (Memory &&m);
	 ~Memory (void);
	 Memory &operator=(const Memory &m);
	 Memory &operator=(Memory &&m);
	 cl_mem get (void) const;
private:
	 Memory (cl_mem m);
	 friend class Context;
	 cl_mem mem;
};

} /* namespace cl */

#endif /* OCLP_MEMORY_H */
