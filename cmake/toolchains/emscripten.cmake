if(NOT EMSCRIPTEN_ROOT AND DEFINED ENV{EMSCRIPTEN_ROOT})
  set(EMSCRIPTEN_ROOT "$ENV{EMSCRIPTEN_ROOT}")
endif()

if(NOT EMSCRIPTEN_ROOT)
  find_program(_emscripten_emcc NAMES emcc REQUIRED)
  get_filename_component(_emscripten_emcc "${_emscripten_emcc}" REALPATH)
  get_filename_component(EMSCRIPTEN_ROOT "${_emscripten_emcc}" DIRECTORY)
endif()

include("${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake")

