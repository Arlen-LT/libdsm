cmake_minimum_required(VERSION 3.22)

project(libdsm
        LANGUAGES C
        VERSION 0.4.3)

add_library(dsm)

INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES("stdatomic.h" HAVE_STDATOMIC_H)

include(CheckTypeSize)
SET(CMAKE_EXTRA_INCLUDE_FILES time.h)
CHECK_TYPE_SIZE("struct timespec" HAVE_STRUCT_TIMESPEC)
SET(CMAKE_EXTRA_INCLUDE_FILES)

if(HAVE_STRUCT_TIMESPEC)
    target_compile_definitions(dsm PRIVATE HAVE_STRUCT_TIMESPEC)
endif()

target_include_directories(dsm PRIVATE
    "src"
    "compat"
    "contrib"
    "include"
    "include/bdsm"
    "include/msvc"
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
)