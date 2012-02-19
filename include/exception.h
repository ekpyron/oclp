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
#ifndef OCLP_EXCEPTION_H
#define OCLP_EXCEPTION_H

#include "common.h"
#include <stdexcept>

namespace cl {

class Exception : public std::exception
{
public:
	 Exception (const char *m, cl_int err);
	 virtual const char *what (void) const throw ();
private:
	 const char *msg;
	 cl_int error;
};

} /* namespace cl */

#endif /* OCLP_EXCEPTION_H */
