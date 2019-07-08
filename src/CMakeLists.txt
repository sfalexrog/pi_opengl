project(pi_opengl_src)

# Find OpenGL ES libraries and link against them

find_library(gles2_lib
    NAMES
        brcmGLESv2
        GLESv2
    HINTS
        /opt/vc/lib
        /usr/lib
)

find_library(egl_lib
    NAMES
        brcmEGL
        EGL
    HINTS
        /opt/vc/lib
        /usr/lib
)

find_path(gles2_header_path
    NAMES
        GLES2/gl2.h
    HINTS
        /opt/vc/include
        /usr/include
)

find_path(egl_header_path
    NAMES
        EGL/egl.h
    HINTS
        /opt/vc/include
        /usr/include
)

add_library(OpenGl INTERFACE)
target_link_libraries(OpenGl INTERFACE ${gles2_lib} ${egl_lib})
target_include_directories(OpenGl INTERFACE ${gles2_header_path} ${egl_header_path})

add_executable(gl_camera
    main.cpp
    util/logger.cpp
    gfx/Shader.cpp
)

if (USE_EGL)
    message(STATUS "Using EGL context")
    find_library(bcm_host_lib
        NAMES
            bcm_host
        HINTS
            /opt/vc/lib
        )

    add_library(BcmHost INTERFACE)
    target_link_libraries(BcmHost INTERFACE ${bcm_host_lib})

    target_sources(gl_camera PRIVATE
        gfx/EGLContext.cpp
        )
    target_link_libraries(gl_camera PUBLIC BcmHost)
    target_compile_definitions(gl_camera PUBLIC USE_EGL)
else()
    message(STATUS "Using SDL GL context")
    target_sources(gl_camera PRIVATE
        gfx/SDLContext.cpp
        )
    target_link_libraries(gl_camera PUBLIC
        SDL2-static
        )
    target_compile_definitions(gl_camera PUBLIC USE_SDL)
endif()

target_include_directories(gl_camera PRIVATE
    .
)

target_link_libraries(gl_camera PUBLIC
    OpenGl
)