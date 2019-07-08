cmake_minimum_required(VERSION 3.1)
project(pi_opengl)

find_file(BcmHostPath bcm_host.h PATHS /opt/vc/include NO_DEFAULT_PATH)
if(NOT BcmHostPath)
    set(HAS_BCM_HOST False)
else()
    set(HAS_BCM_HOST True)
endif()

option(USE_EGL "Use EGL instead of SDL for context creation" ${HAS_BCM_HOST})

add_subdirectory(vendor)
add_subdirectory(data)
add_subdirectory(src)
