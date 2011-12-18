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
#ifndef CLP_KERNEL_H
#define CLP_KERNEL_H

#include "common.h"
#include "memory.h"

namespace cl {

class Kernel
{
public:
	 Kernel (void);
	 Kernel (const Kernel &k);
	 Kernel (Kernel &&k);
	 ~Kernel (void);
	 Kernel &operator= (const Kernel &k);
	 Kernel &operator= (Kernel &&k);
	 void SetArg (cl_uint arg_index, size_t arg_size, const void *arg_value);
	 void SetArg (cl_uint arg_index, const Memory &memory);
	 cl_kernel get (void) const;
private:
	 Kernel (cl_kernel k);
	 friend class Program;
	 cl_kernel kernel;
};

} /* namespace cl */

#endif /* CLP_KERNEL_H */
