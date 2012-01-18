# Copyright (c) 2011 Daniel Kirchner
#
# This file is part of oclp.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
#
# - Find OpenCL library
# Once done this will define
#
#   OPENCL_FOUND		- system has OpenCL
#   OPENCL_INCLUDE_DIR		- the OpenCL include directory
#   OPENCL_LIBRARY		- link these to use OpenCL
#

find_path (OPENCL_INCLUDE_DIR CL/cl.hpp)
find_library (OPENCL_LIBRARY NAMES OpenCL)
if (OPENCL_LIBRARY)
  set (OPENCL_FOUND TRUE)
else (OPENCL_LIBRARY)
  set (OPENCL_FOUND FALSE)
endif (OPENCL_LIBRARY)
