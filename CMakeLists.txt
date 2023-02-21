cmake_minimum_required(VERSION 3.23)

include(CheckIncludeFiles)
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckTypeSize)
include(CheckCXXSourceCompiles)
include(CheckStructHasMember)
include(TestBigEndian)

project(dsm
        LANGUAGES C
        VERSION 0.4.3)

check_include_files("inttypes.h" HAVE_INTTYPES_H)
check_include_files("stdatomic.h" HAVE_STDATOMIC_H)
check_include_files("stdlib.h" HAVE_STDLIB_H)
check_include_files("strings.h" HAVE_STRINGS_H)
check_include_files("string.h" HAVE_STRING_H)
check_include_files("bsd/string.h" HAVE_BSD_STRING_H)
check_include_files("alloca.h" HAVE_ALLOCA_H)
check_include_files("sys/queue.h" HAVE_SYS_QUEUE_H)
check_include_files("arpa/inet.h" HAVE_ARPA_INET_H)
check_include_files("sys/socket.h" HAVE_SYS_SOCKET_H)
check_include_files("time.h" HAVE_TIME_H)
check_include_files("sys/stat.h" HAVE_SYS_STAT_H)
check_include_files("sys/types.h" HAVE_SYS_TYPES_H)
check_include_files("ifaddrs.h" HAVE_IFADDRS_H)
check_include_files("unistd.h" HAVE_UNISTD_H)

if (HAVE_TIME_H)
    check_struct_has_member("struct timespec" tv_sec "time.h" HAVE_STRUCT_TIMESPEC)
endif (HAVE_TIME_H)
# FUNCTIONS
CHECK_FUNCTION_EXISTS(strndup HAVE_STRNDUP)
CHECK_FUNCTION_EXISTS(strlcpy HAVE_STRLCPY)
CHECK_FUNCTION_EXISTS(pipe HAVE_PIPE)
CHECK_FUNCTION_EXISTS(_pipe HAVE__PIPE)
check_function_exists(calloc HAVE_CALLOC)
check_function_exists(exit HAVE_EXIT)
check_function_exists(fprintf HAVE_FPRINTF)
check_function_exists(free HAVE_FREE)
check_function_exists(longjmp HAVE_LONGJMP)
check_function_exists(malloc HAVE_MALLOC)
check_function_exists(memcpy HAVE_MEMCPY)
check_function_exists(memset HAVE_MEMSET)
check_function_exists(printf HAVE_PRINTF)
check_function_exists(setjmp HAVE_SETJMP)
check_function_exists(signal HAVE_SIGNAL)
check_function_exists(strsignal HAVE_STRSIGNAL)
check_function_exists(sprintf HAVE_SNPRINTF)
check_function_exists(strcmp HAVE_STRCMP)
check_function_exists(vsnprintf HAVE_VSNPRINTF)
check_function_exists(clock_gettime HAVE_CLOCK_GETTIME)
if (WIN32)
    check_function_exists(_vsnprintf_s HAVE__VSNPRINTF_S)
    check_function_exists(_vsnprintf HAVE__VSNPRINTF)
    check_function_exists(_snprintf HAVE__SNPRINTF)
    check_function_exists(_snprintf_s HAVE__SNPRINTF_S)
endif (WIN32)
check_type_size(clockid_t HAVE_CLOCKID_T)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h"
)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()


add_library(dsm STATIC)

target_compile_definitions(${PROJECT_NAME} 
    PRIVATE $<IF:$<CONFIG:Debug>,DEBUG,NDEBUG>
    PRIVATE HAVE_CONFIG_H
    PRIVATE $<$<BOOL:${MSVC}>:_UNICODE UNICODE _CONSOLE>
)

if(WIN32)
target_link_libraries(dsm
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/win64/libiconv.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/win64/libtasn1.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/win64/libpthreadVC3d.lib"
)
else()
target_link_libraries(dsm
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/armv7/libiconv.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/armv7/libtasn1.a"
)
endif()

target_include_directories(dsm PRIVATE
    "src"
    "compat"
    "contrib"
    "include"
    "$<$<BOOL:${MSVC}>:${CMAKE_CURRENT_SOURCE_DIR}/include/msvc>"
)
target_sources(dsm PRIVATE 
    "src/hmac_md5.c"
    "src/netbios_ns.c"
    "src/netbios_query.c"
    "src/netbios_session.c"
    "src/netbios_utils.c"
    "src/smb_buffer.c"
    "src/smb_dir.c"
    "src/smb_fd.c"
    "src/smb_file.c"
    "src/smb_message.c"
    "src/smb_ntlm.c"
    "src/smb_session.c"
    "src/smb_session_msg.c"
    "src/smb_share.c"
    "src/smb_spnego.c"
    "src/smb_stat.c"
    "src/smb_trans2.c"
    "src/smb_transport.c"
    "src/smb_utils.c"
    "contrib/mdx/md4.c"
    "contrib/mdx/md5.c"
    "contrib/rc4/rc4.c"
    "contrib/spnego/spnego_asn1.c"

    "$<$<BOOL:${MSVC}>:${CMAKE_CURRENT_SOURCE_DIR}/compat/strlcpy.c>"
    "$<$<BOOL:${MSVC}>:${CMAKE_CURRENT_SOURCE_DIR}/compat/strndup.c>"
 )