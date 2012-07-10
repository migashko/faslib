project(config CXX C)
INCLUDE (${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
INCLUDE (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
INCLUDE (${CMAKE_ROOT}/Modules/CheckLibraryExists.cmake)

check_include_file("sys/time.h" HAVE_SYS_TIME_H)
check_include_file("sys/resource.h" HAVE_SYS_RESORCE_H)
check_include_file("sys/timeb.h" HAVE_SYS_TIMEB_H)

check_include_file("unistd.h" HAVE_UNISTD_H)
check_include_file("io.h" HAVE_IO_H)
check_include_file("Windows.h" HAVE_WINDOWS_H)
check_include_file("Wincon.h" HAVE_WINCON_H)

set(
  CMAKE_REQUIRED_INCLUDES 
  ${CMAKE_REQUIRED_INCLUDES} 
  "sys/time.h"
  "sys/resource.h"
  "sys/timeb.h"
  "unistd.h"
  "io.h"
  "Windows.h" 
  "Wincon.h"
)

check_function_exists("gettimeofday" HAVE_GETTIMEOFDAY_FUNC)
check_function_exists("socket" HAVE_SOCKET_FUNC)
check_function_exists("ftime" HAVE_FTIME_FUNC)
check_function_exists("_ftime" HAVE__FTIME_FUNC)
check_function_exists("_ftime32_s" HAVE__FTIME_S_FUNC)
check_function_exists("_ftime64_s" HAVE__FTIME_S_FUNC)
check_function_exists("isatty" HAVE_ISATTY_FUNC)
check_function_exists("_isatty" HAVE__ISATTY_FUNC)
check_function_exists("getrusage" HAVE_GETRUSAGE_FUNC)
check_function_exists("SetConsoleTextAttribute" HAVE_SETCONSOLETEXTATTRIBUTE_FUNC)

check_library_exists(rt clock_gettime "time.h" HAVE_RT_LIB)

if(HAVE_RT_LIB)
  message(STATUS "FAS_USE_RT_LIB ON ")
  SET(FAS_USE_RT_LIB ON PARENT_SCOPE)
  SET (CMAKE_REQUIRED_LIBRARIES rt)
  check_function_exists(clock_gettime HAVE_CLOCK_GETTIME_FUNC)
  SET (CMAKE_REQUIRED_LIBRARIES)
else(HAVE_RT_LIB)
  message(STATUS "FAS_USE_RT_LIB OFF")
  SET(FAS_USE_RT_LIB OFF PARENT_SCOPE)
endif(HAVE_RT_LIB)

configure_file("${PROJECT_SOURCE_DIR}/config/config.h.in"
               "${PROJECT_SOURCE_DIR}/fas/system/config.h" )
