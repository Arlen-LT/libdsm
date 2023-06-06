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
check_symbol_exists(strndup "string.h" HAVE_STRNDUP)
check_symbol_exists(strlcpy "string.h" HAVE_STRLCPY)
check_symbol_exists(pipe "" HAVE_PIPE)
check_symbol_exists(_pipe "" HAVE__PIPE)
check_symbol_exists(calloc "" HAVE_CALLOC)
check_symbol_exists(exit "" HAVE_EXIT)
check_symbol_exists(fprintf "" HAVE_FPRINTF)
check_symbol_exists(free "" HAVE_FREE)
check_symbol_exists(longjmp "" HAVE_LONGJMP)
check_symbol_exists(malloc "" HAVE_MALLOC)
check_symbol_exists(memcpy "" HAVE_MEMCPY)
check_symbol_exists(memset "" HAVE_MEMSET)
check_symbol_exists(printf "" HAVE_PRINTF)
check_symbol_exists(setjmp "" HAVE_SETJMP)
check_symbol_exists(signal "" HAVE_SIGNAL)
check_symbol_exists(strsignal "" HAVE_STRSIGNAL)
check_symbol_exists(sprintf "" HAVE_SNPRINTF)
check_symbol_exists(strcmp "" HAVE_STRCMP)
check_symbol_exists(vsnprintf "" HAVE_VSNPRINTF)
check_symbol_exists(clock_gettime "time.h" HAVE_CLOCK_GETTIME)
check_symbol_exists(nl_langinfo "" HAVE_NL_LANGINFO)
if (WIN32)
    check_symbol_exists(_vsnprintf_s "stdio.h" HAVE__VSNPRINTF_S)
    check_symbol_exists(_vsnprintf "stdio.h" HAVE__VSNPRINTF)
    check_symbol_exists(_snprintf "stdio.h" HAVE__SNPRINTF)
    check_symbol_exists(_snprintf_s "stdio.h" HAVE__SNPRINTF_S)
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
    PRIVATE ASN1_DISABLE_DEPRECATED
)

target_compile_options(dsm PRIVATE -Wall -Wsign-compare -Wextra -Wstrict-aliasing -Wstrict-overflow)

if(WIN32)
    find_package(PThreads4W REQUIRED)
    find_package(Iconv REQUIRED)
    check_symbol_exists(iconv_open "iconv.h" HAVE_ICONV_OPEN)
    if(NOT HAVE_ICONV_OPEN)
        message(FATAL_ERROR "iconv is not available")
    endif()

    include(FindPkgConfig)
    pkg_check_modules(TASN1 REQUIRED libtasn1>=4.19.0)

    target_include_directories(dsm INTERFACE ${TASN1_INCLUDE_DIRS})
    target_link_libraries(dsm PRIVATE 
        ${TASN1_LIBRARY_DIRS}/${TASN1_LIBRARIES}.lib
        Iconv::Iconv
        PThreads4W::PThreads4W
    )
elseif(${CMAKE_ANDROID_ARCH_ABI} STREQUAL "armeabi-v7a")
    target_link_libraries(dsm
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/armv7/libiconv.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/armv7/libtasn1.a"
    )
elseif(${CMAKE_ANDROID_ARCH_ABI} STREQUAL "arm64-v8a")
    set(Iconv_IS_BUILT_IN False)
    find_package(Iconv REQUIRED)
    check_symbol_exists(iconv_open "iconv.h" HAVE_ICONV_OPEN)
    if(NOT HAVE_ICONV_OPEN)
        message(FATAL_ERROR "iconv is not available")
    endif()

    include(FindPkgConfig)
    pkg_check_modules(TASN1 REQUIRED libtasn1>=4.19.0)

    target_include_directories(dsm INTERFACE ${TASN1_INCLUDE_DIRS})
    target_link_libraries(dsm PRIVATE 
        ${TASN1_LIBRARY_DIRS}/lib${TASN1_LIBRARIES}.a
        Iconv::Iconv
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