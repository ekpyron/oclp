lib_LTLIBRARIES = liboclp.la
liboclp_la_SOURCES = commandqueue.cpp context.cpp exception.cpp kernel.cpp memory.cpp program.cpp
liboclp_la_CXXFLAGS = -I $(top_srcdir)/include
liboclp_la_includedir=$(includedir)/oclp
liboclp_la_include_HEADERS = $(top_srcdir)/include/oclp.h $(top_srcdir)/include/commandqueue.h $(top_srcdir)/include/common.h $(top_srcdir)/include/context.h $(top_srcdir)/include/exception.h $(top_srcdir)/include/kernel.h $(top_srcdir)/include/memory.h $(top_srcdir)/include/program.h $(top_srcdir)/include/config.h
liboclp_la_CPPFLAGS = $(DEPS_CFLAGS)
liboclp_la_LIBADD = $(DEPS_LIBS)
liboclp_la_LIBRARY_VERSION = 0:0:0
liboclp_la_LDFLAGS = -version-info $(liboclp_la_LIBRARY_VERSION)
