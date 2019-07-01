project(pi_opengl_vendor)

# Optional dependency: glslang (reference shader compiler)

if (EXISTS "${PROJECT_SOURCE_DIR}/glslang/CMakeLists.txt")
    add_subdirectory(glslang)
endif()

# Optional dependency: SDL2 (for local debug)

if (EXISTS "${PROJECT_SOURCE_DIR}/SDL2/CMakeLists.txt")
    add_subdirectory(SDL2)
endif()

# Optional dependency: Raspberry Pi userland software (used only for headers)

if (EXISTS "${PROJECT_SOURCE_DIR}/userland/CMakeLists.txt")
    # We intentionally don't use CMakeLists.txt
    message(STATUS "Adding userland directories to include paths")
    include_directories("userland")
    include_directories("userland/host_applications/")
endif()
