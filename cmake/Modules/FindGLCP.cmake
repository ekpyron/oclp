# Copyright (c) 2011 Daniel Kirchner
#
# This file is part of clp.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
#
# - Find GLCP library 
# Once done this will define
#
#   GLCP_FOUND		- system has GLCP
#   GLCP_INCLUDE_DIR	- the GLCP include directory
#   GLCP_LIBRARY	- link these to use GLCP
# 

find_path (GLCP_INCLUDE_DIR glcp.h)
find_library (GLCP_LIBRARY NAMES glcp)
if (GLCP_LIBRARY)
  set (GLCP_FOUND TRUE)
else (GLCP_LIBRARY)
  set (GLCP_FOUND FALSE)
endif (GLCP_LIBRARY)
