cmake_minimum_required(VERSION 3.18)

project(libdsm
        LANGUAGES C
        VERSION 0.4.3)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

include (CheckFunctionExists)
CHECK_FUNCTION_EXISTS(strndup HAVE_STRNDUP)

INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES("stdatomic.h" HAVE_STDATOMIC_H)
CHECK_INCLUDE_FILES("unistd.h" HAVE_UINTSTD_H)
CHECK_INCLUDE_FILES("ifaddrs.h" HAVE_IFADDRS_H)
CHECK_INCLUDE_FILES("sys/queue.h" HAVE_SYS_QUEUE_H)
CHECK_INCLUDE_FILES("sys/socket.h" HAVE_SYS_SOCKET_H)
CHECK_INCLUDE_FILES("sys/time.h" HAVE_SYS_TIME_H)
CHECK_INCLUDE_FILES("arpa/inet.h" HAVE_ARPA_INET_H)

include(CheckTypeSize)
SET(CMAKE_EXTRA_INCLUDE_FILES time.h)
CHECK_TYPE_SIZE("struct timespec" HAVE_STRUCT_TIMESPEC)
SET(CMAKE_EXTRA_INCLUDE_FILES)

add_library(dsm STATIC)

if(MSVC AND BUILD_SHARED_LIBS)
    set_target_properties(dsm PROPERTIES DEF_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/dsm.def)
    set_target_properties(dsm PROPERTIES CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEF:${DEF_FILE_PATH}")

endif()

if(WIN32)
target_link_libraries(dsm 
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libiconv.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libtasn1.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libpthreadVC3d.lib"
    ws2_32
)
endif()

if(HAVE_STDATOMIC_H)
    target_compile_definitions(dsm PRIVATE HAVE_STDATOMIC_H)
endif()
if(HAVE_UINTSTD_H)
    target_compile_definitions(dsm PUBLIC HAVE_UINTSTD_H)
endif()
if(HAVE_IFADDRS_H)
    target_compile_definitions(dsm PUBLIC HAVE_IFADDRS_H)
endif()
if(HAVE_SYS_QUEUE_H)
    target_compile_definitions(dsm PUBLIC HAVE_SYS_QUEUE_H)
endif()
if(HAVE_SYS_SOCKET_H)
    target_compile_definitions(dsm PUBLIC HAVE_SYS_SOCKET_H)
endif()
if(HAVE_SYS_TIME_H)
    target_compile_definitions(dsm PUBLIC HAVE_SYS_TIME_H)
endif()
if(HAVE_ARPA_INET_H)
    target_compile_definitions(dsm PUBLIC HAVE_ARPA_INET_H)
endif()
if(HAVE_STRUCT_TIMESPEC)
    target_compile_definitions(dsm PUBLIC HAVE_STRUCT_TIMESPEC)
endif()

target_include_directories(dsm PRIVATE
    "src"
    "compat"
    "contrib"
    "include"
    "include/bdsm"
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
    "compat/strlcpy.c"
    "compat/strndup.c"
    "contrib/spnego/spnego_asn1.c"
)