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
#ifndef OCLP_PROGRAM_H
#define OCLP_PROGRAM_H

#include "common.h"

namespace cl {

class Program
{
public:
	 Program (void);
	 Program (const Program &p);
	 Program (Program &&p);
	 ~Program (void);
	 Program &operator= (const Program &p);
	 Program &operator= (Program &&p);
	 static void UnloadCompiler (void);
	 void Build (const std::string &options);
	 Kernel CreateKernel (const char *kernel_name);
private:
	 Program (cl_program p);
	 cl_program program;
	 friend class Context;
};

} /* namespace cl */

#endif /* OCLP_PROGRAM_H */
