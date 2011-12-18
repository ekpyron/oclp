# Copyright (c) 2011 Daniel Kirchner
#
# This file is part of clp.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.
#
# - Find GLP library 
# Once done this will define
#
#   GLP_FOUND		- system has GLP
#   GLP_INCLUDE_DIR	- the GLP include directory
#   GLP_LIBRARY		- link these to use GLP
# 

find_path (GLP_INCLUDE_DIR glp.h)
find_library (GLP_LIBRARY NAMES glp)
if (GLP_LIBRARY)
  set (GLP_FOUND TRUE)
else (GLP_LIBRARY)
  set (GLP_FOUND FALSE)
endif (GLP_LIBRARY)
