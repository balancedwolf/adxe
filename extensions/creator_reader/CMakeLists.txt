# reader lib for creator to cocos2d-x plugin
set(cocos_root ${ADXE_ROOT_PATH})

set(LIB_NAME creator_reader)

include_directories(
    collider
    animation
    ${cocos_root}/extensions/DragonBones/cocos2dx
    ${cocos_root}/extensions/DragonBones/armature
    ${cocos_root}/extensions/DragonBones/animation
    ${cocos_root}/extensions/DragonBones/events
    ${cocos_root}/extensions/DragonBones/factories
    ${cocos_root}/extensions/DragonBones/core
    ${cocos_root}/extensions/DragonBones/geom
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${cocos_root}/core
    ${cocos_root}/cocos/editor-support
    ${cocos_root}/extensions/spine/
    ${cocos_root}/extensions/spine/runtime/include
    ${cocos_root}/thirdparty/robin-map/include
    ${cocos_root}/thirdparty/glad/include
    ${cocos_root}/thirdparty/glfw/include/GLFW
    ${cocos_root}/thirdparty/
)

set(READER_HEADER
    CreatorReader_generated.h
    CreatorReader.h
    animation/Easing.h
    animation/AnimateClip.h
    animation/Bezier.h
    animation/AnimationClipProperties.h
    animation/AnimationManager.h
    animation/AnimationClip.h
    collider/Collider.h
    collider/Intersection.h
    collider/ColliderManager.h
    collider/Contract.h
    Macros.h
    ui/RichtextStringVisitor.h
    ui/PageView.h
)

set(READER_SOURCE
    animation/AnimateClip.cpp
    animation/AnimationClip.cpp
    animation/AnimationManager.cpp
    animation/Easing.cpp
    animation/Bezier.cpp
    collider/Collider.cpp
    collider/ColliderManager.cpp
    collider/Contract.cpp
    collider/Intersection.cpp
    CreatorReader.cpp
    ui/PageView.cpp
    ui/RichtextStringVisitor.cpp
)

if(BUILD_LUA_LIBS)
    list(APPEND READER_HEADER
        lua-bindings/reader/lua_creator_reader_auto.hpp
        lua-bindings/reader/lua_creator_reader_manual.hpp
        lua-bindings/dragonbones/lua_dragonbones_auto.hpp
        lua-bindings/dragonbones/lua_dragonbones_manual.hpp
        lua-bindings/creator_reader_bindings.hpp
    )
    list(APPEND READER_SOURCE
        lua-bindings/creator_reader_bindings.cpp
        lua-bindings/reader/lua_creator_reader_auto.cpp
        lua-bindings/reader/lua_creator_reader_manual.cpp
        lua-bindings/dragonbones/lua_dragonbones_manual.cpp
        lua-bindings/dragonbones/lua_dragonbones_auto.cpp
    )
endif()


add_library(${LIB_NAME} ${READER_SOURCE} ${READER_HEADER})

set_target_properties(${LIB_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "Extensions"
)

target_link_libraries(${LIB_NAME} DragonBones)

if(XCODE OR VS)
    cocos_mark_code_files(${LIB_NAME})
endif()

setup_cocos_extension_config(${LIB_NAME})

