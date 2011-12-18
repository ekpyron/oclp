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
	stream << msg << ": " << error;
	return stream.str ().c_str ();
}

} /* namespace cl */
