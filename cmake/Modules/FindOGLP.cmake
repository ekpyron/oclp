# Copyright (c) 2011 Daniel Kirchner
#
# This file is part of oclp.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
#
# - Find OGLP library 
# Once done this will define
#
#   OGLP_FOUND		- system has OGLP
#   OGLP_INCLUDE_DIR	- the OGLP include directory
#   OGLP_LIBRARY	- link these to use OGLP
# 

find_path (OGLP_INCLUDE_DIR oglp.h)
find_library (OGLP_LIBRARY NAMES oglp)
if (OGLP_LIBRARY)
  set (OGLP_FOUND TRUE)
else (OGLP_LIBRARY)
  set (OGLP_FOUND FALSE)
endif (OGLP_LIBRARY)
