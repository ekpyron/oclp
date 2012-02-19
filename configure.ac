AC_INIT([oclp], [0.0], [daniel@ekpyron.org])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
LT_INIT
CXXFLAGS="$CXXFLAGS -std=c++0x"
AC_PROG_CXX
AC_LANG([C++])
AC_LANG_CPLUSPLUS

AC_CONFIG_MACRO_DIR([m4])

AC_ARG_WITH([glm],
	[AS_HELP_STRING([--with-glm=DIR],
			[location of the glm headers])],
	[CPPFLAGS="-I$withval ${CPPFLAGS}"])
AC_CHECK_HEADERS(glm/glm.hpp, [], AC_MSG_FAILURE([glm headers missing]))

AC_ARG_WITH([opencl-headers],
	[AS_HELP_STRING[--with-opencl-headers=DIR],
			[location of the opencl headers])],
	[AS_IF([test "x$withval" != xyes],
		[CPPFLAGS="-I$withval ${CPPFLAGS}"
		 CL_CFLAGS="-I$withval"
		 AC_SUBST(CL_CFLAGS)]]))
AC_CHECK_HEADERS(CL/cl.h, [], AC_MSG_FAILURE([opencl headers missing]))

AC_ARG_WITH([opencl-libdir],
	[AS_HELP_STRING[--with-opencl-libdir=DIR],
			[location of the opencl libraries])],
	[AS_IF([test "x$withval" != xyes],
		[CL_LDFLAGS="-L$withval"
		LDFLAGS="${CL_LDFLAGS} $LDFLAGS"])])
AC_CHECK_LIB(OpenCL, clFinish,
	[LIBS="-lOpenCL ${LIBS}"
	 CL_LIBS="${CL_LDFLAGS} -lOpenCL"
	 AC_SUBST(CL_LIBS)
	],
	AC_MSG_FAILURE([could not link with opencl]))

PKG_CHECK_MODULES([DEPS], [oglp])

AX_CHECK_GL

AC_CONFIG_FILES([Makefile src/Makefile oclp.pc])
AC_OUTPUT
