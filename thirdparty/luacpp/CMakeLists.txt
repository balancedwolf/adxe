set(lib_name luacpp)
set(target_name ${lib_name})

project(${lib_name})

# Source files
set(${target_name}_src
	LuaCpp.hpp
	LuaVersion.cpp LuaVersion.hpp
	Engine/LuaState.cpp Engine/LuaState.hpp
	Engine/LuaType.cpp Engine/LuaType.hpp
	Engine/LuaTNil.cpp Engine/LuaTNil.hpp
	Engine/LuaTString.cpp Engine/LuaTString.hpp
	Engine/LuaTNumber.cpp Engine/LuaTNumber.hpp
	Engine/LuaTBoolean.cpp Engine/LuaTBoolean.hpp
	Engine/LuaTTable.cpp Engine/LuaTTable.hpp
	Engine/LuaTUserData.cpp Engine/LuaTUserData.hpp
	Registry/LuaRegistry.cpp Registry/LuaRegistry.hpp
	Registry/LuaCodeSnippet.cpp Registry/LuaCodeSnippet.hpp
	Registry/LuaCompiler.cpp Registry/LuaCompiler.hpp
	Registry/LuaCFunction.cpp Registry/LuaCFunction.hpp
	Registry/LuaLibrary.cpp Registry/LuaLibrary.hpp
	LuaContext.cpp LuaContext.hpp
	LuaMetaObject.cpp LuaMetaObject.hpp
)


add_library(${target_name} STATIC
  ${${target_name}_src}
)

if(NOT AX_USE_LUAJIT)
  target_include_directories(${target_name} PRIVATE ../lua/${AX_LUA_ENGINE})
else()
  target_include_directories(${target_name} PRIVATE ../lua/${AX_LUA_ENGINE}/include)
endif()

target_include_directories(${target_name} PUBLIC ../lua/sol2)
target_include_directories(${target_name} PUBLIC .)

set_target_properties(${target_name}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "ThirdParty"
)
