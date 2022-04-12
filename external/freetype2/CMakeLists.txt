cmake_minimum_required(VERSION 3.6)

set(lib_name freetype)
set(target_name ext_${lib_name})

project(${lib_name})

include(../cmake/CocosExternalConfig.cmake)

add_library(${target_name} STATIC IMPORTED GLOBAL)

if(WINDOWS)
  if(CMAKE_SYSTEM_NAME STREQUAL "WindowsStore")
    set_target_properties(${target_name} PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/win10/freetype2"
    )
  else()
    set_target_properties(${target_name} PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/${platform_name}/freetype2"
    )
  endif()
else()
  set_target_properties(${target_name} PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/${platform_name}/freetype2"
  )
endif()


if(WINDOWS)
  if(CMAKE_SYSTEM_NAME STREQUAL "WindowsStore")
    set_target_properties(${target_name} PROPERTIES
      IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/win10/${lib_name}.lib"
    )
  else()
    set_target_properties(${target_name} PROPERTIES
      IMPORTED_LOCATION "${platform_spec_path}/${lib_name}.lib"
    )

  endif()
else()
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/lib${lib_name}.a"
  )
endif()
