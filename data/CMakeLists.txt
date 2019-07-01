project(pi_opengl_data)

add_custom_target(Shaders)

if (TARGET glslangValidator)
    message(STATUS "Enabling shader validation")
    file(GLOB GLSL_SOURCE_FILES
        *.vert
        *.frag
    )

    foreach(GLSL ${GLSL_SOURCE_FILES})
        get_filename_component(FILE_NAME ${GLSL} NAME)
        string(REPLACE "/" "_" GLSL_SAFE ${GLSL})
        add_custom_target(
                Check_Shader_${GLSL_SAFE}
                COMMAND glslangValidator ${GLSL}
                DEPENDS ${GLSL}
        )
        add_dependencies(Shaders Check_Shader_${GLSL_SAFE})
    endforeach()
endif()
