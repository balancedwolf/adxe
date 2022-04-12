cmake_minimum_required(VERSION 3.6)

set(lib_name_egl EGL)
set(target_name_egl ext_${lib_name_egl})

set(lib_name_gles GLESV2)
set(target_name_gles ext_${lib_name_gles})


set(target_name ext_angle)

project(${target_name_egl})
project(${target_name_gles})

include(../../cmake/CocosExternalConfig.cmake)

add_library(${target_name_egl} SHARED IMPORTED GLOBAL)
add_library(${target_name_gles} SHARED IMPORTED GLOBAL)

set_target_properties(${target_name_egl} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(${target_name_gles} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
)


set_target_properties(${target_name_egl} PROPERTIES
  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libEGL.dll"
  IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libEGL.lib"
)

set_target_properties(${target_name_gles} PROPERTIES
  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libGLESv2.dll"
  IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/libGLESv2.lib"
)