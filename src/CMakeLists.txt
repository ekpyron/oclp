# Copyright (c) 2011 Daniel Kirchner
#
# This file is part of clp.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
#
file (GLOB CLP_SOURCES *.cpp)
find_package (OpenCL REQUIRED)
find_package (GLCP REQUIRED)
include_directories (include ${OPENCL_INCLUDE_DIR} ${GLCP_INCLUDE_DIR})

add_library (clp STATIC ${CLP_SOURCES})

target_link_libraries (clp ${OPENCL_LIBRARY} ${GLCP_LIBRARY})

set_property (TARGET clp PROPERTY
  COMPILE_FLAGS -std=c++0x)

set_target_properties (clp PROPERTIES
		      	   PUBLIC_HEADER "include/clp.h;include/commandqueue.h;include/context.h;include/exception.h;include/kernel.h;include/memory.h;include/program.h;include/common.h")

install (TARGETS clp ARCHIVE DESTINATION lib
		     RUNTIME DESTINATION bin
		     LIBRARY DESTINATION lib
		     PUBLIC_HEADER DESTINATION include/clp)
