set(CMAKE_POLICY_VERSION_MINIMUM 3.10)

if(MSVC)
  add_compile_options(/W0)
else()
  add_compile_options(-w)
endif()

if(NOT EMSCRIPTEN)
  add_subdirectory(glew-cmake SYSTEM)
  add_subdirectory(glfw SYSTEM)
endif()

add_subdirectory(glm SYSTEM)

set(IMGUI_WITH_BACKEND ON CACHE BOOL "" FORCE)
set(IMGUI_BACKEND_PLATFORM "GLFW" CACHE STRING "" FORCE)
add_subdirectory(cmake-imgui SYSTEM)
if(EMSCRIPTEN)
  target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_ES3 GLFW_INCLUDE_NONE)
  target_compile_options(imgui PRIVATE "-sUSE_GLFW=3")
else()
  target_link_libraries(imgui PUBLIC glfw)
endif()
target_sources(imgui PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake-imgui/imgui/backends/imgui_impl_opengl3.cpp"
)

add_subdirectory(stb-cmake SYSTEM)
