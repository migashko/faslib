#ifndef FAS_SYSTEM_UNP_HPP
#define FAS_SYSTEM_UNP_HPP

#include <fas/system/config.h>

#include <cstdio>
#include <cstdlib>

/* Define to 1 if you have the <sys/time.h> header file. */
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef HAVE_SYS_RESORCE_H
#include <sys/resource.h> 
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif


/* Define to 1 if you have the <sys/timeb.h> header file. */
#ifdef HAVE_SYS_TIMEB_H
#include <sys/timeb.h>
#endif

/* Define to 1 if you have the <windows.h> header file. */
#ifdef HAVE_WINDOWS_H
#include <windows.h>
#endif

/* Define to 1 if you have the <io.h> header file. */
#ifdef HAVE_IO_H
#include <io.h>
#endif

#endif
