set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
add_compile_options(-w)

add_subdirectory(glew-cmake SYSTEM)

add_subdirectory(glfw SYSTEM)

add_subdirectory(glm SYSTEM)

set(IMGUI_WITH_BACKEND ON CACHE BOOL "" FORCE)
set(IMGUI_BACKEND_PLATFORM "GLFW" CACHE STRING "" FORCE)
add_subdirectory(cmake-imgui SYSTEM)
target_sources(imgui PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake-imgui/imgui/backends/imgui_impl_opengl3.cpp"
)

add_subdirectory(stb-cmake SYSTEM)
