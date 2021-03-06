include(uLibMacros)
include_guard(ULIB_CONFIG_HEADER_CMAKE)


## CONFIG ------------------------------------------------------------------- ##

message("/////////// CONFIG HEADER //////////////")

include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)

## force to use PP variadics (FIX) ##
set(BOOST_PP_VARIADICS ON)

message(STATUS "PROJECT NAME = ${PROJECT_NAME}")
message(STATUS "PACKAGE VERSION = ${PACKAGE_VERSION}")
message(STATUS "PACKAGE NAME = ${PACKAGE_NAME}")

CHECK_INCLUDE_FILES(inittypes.h HAVE_INITTYPES_H)
CHECK_INCLUDE_FILES(stdbool.h HAVE_STDBOOL_H)
CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)
CHECK_INCLUDE_FILES(stdlib.h HAVE_STDLIB_H)

CHECK_INCLUDE_FILES(dlfcn.h HAVE_DLFCN_H)
CHECK_INCLUDE_FILES(malloc.h HAVE_MALLOC_H)
CHECK_FUNCTION_EXISTS(malloc HAVE_MALLOC)
CHECK_INCLUDE_FILES(memory.h HAVE_MEMORY_H)

CHECK_INCLUDE_FILES(math.h HAVE_MATH_H)
CHECK_FUNCTION_EXISTS(fsetround HAVE_FSETROUND)
CHECK_FUNCTION_EXISTS(floor HAVE_FLOOR)
CHECK_FUNCTION_EXISTS(pow HAVE_POW)
CHECK_FUNCTION_EXISTS(sqrt HAVE_SQRT)

CHECK_FUNCTION_EXISTS(strdup HAVE_STRDUP)
CHECK_FUNCTION_EXISTS(strstr HAVE_STRSTR)
CHECK_INCLUDE_FILES(strings.h HAVE_STRINGS_H)
CHECK_INCLUDE_FILES(string.h HAVE_STRING_H)

CHECK_INCLUDE_FILES(sys/stat.h HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)

CHECK_INCLUDE_FILES(assert.h HAVE_ASSERT_H)


configure_file(
  "${PROJECT_SOURCE_DIR}/CMakeConfig.in.h"
  "${PROJECT_BINARY_DIR}/config.h"
  )
