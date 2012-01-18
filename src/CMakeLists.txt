# Copyright (c) 2011 Daniel Kirchner
#
# This file is part of oclp.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
#
file (GLOB OCLP_SOURCES *.cpp)
find_package (OpenCL REQUIRED)
find_package (OGLP REQUIRED)
find_package (GLM REQUIRED)
include_directories (include ${OPENCL_INCLUDE_DIR} ${OGLP_INCLUDE_DIR}
		     ${GLM_INCLUDE_DIR})

add_library (oclp STATIC ${OCLP_SOURCES})

target_link_libraries (oclp ${OPENCL_LIBRARY} ${OGLP_LIBRARY})

set_property (TARGET oclp PROPERTY
  COMPILE_FLAGS -std=c++0x)

set_target_properties (oclp PROPERTIES
		      	   PUBLIC_HEADER "include/oclp.h;include/commandqueue.h;include/context.h;include/exception.h;include/kernel.h;include/memory.h;include/program.h;include/common.h")

install (TARGETS oclp ARCHIVE DESTINATION lib
		     RUNTIME DESTINATION bin
		     LIBRARY DESTINATION lib
		     PUBLIC_HEADER DESTINATION include/oclp)
