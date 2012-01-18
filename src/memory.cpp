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

Memory::Memory (void) : mem (NULL)
{
}

Memory::Memory (cl_mem m) : mem (m)
{
}

Memory::Memory (Memory &&m) : mem (m.mem)
{
	m.mem = NULL;
}

Memory::Memory (const Memory &m) : mem (m.mem)
{
	if (mem)
	{
		 clRetainMemObject (mem);
	}
}

Memory::~Memory (void)
{
	if (mem != NULL)
	{
		clReleaseMemObject (mem);
		mem = NULL;
	}
}

Memory &Memory::operator= (Memory &&m)
{
	mem = m.mem;
	m.mem = NULL;
	return *this;
}

Memory &Memory::operator= (const Memory &m)
{
	mem = m.mem;
	if (mem != NULL)
	{
		clReleaseMemObject (mem);
	}
	return *this;
}

cl_mem Memory::get (void) const
{
	return mem;
}

} /* namespace cl */
