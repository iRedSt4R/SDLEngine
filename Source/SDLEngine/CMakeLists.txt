LINK_DIRECTORIES(${ENGINE_OUTPUT_DIR})
INCLUDE_DIRECTORIES(${TP_SDL2_INCLUDE_DIR})

# Files for static library build
file(GLOB_RECURSE SourceFiless
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

#define output (static lib)
add_library(${ENGINE_LIBRARY_NAME} STATIC ${SourceFiless})
target_link_libraries(${ENGINE_LIBRARY_NAME} SDL2.lib)
target_link_libraries(${ENGINE_LIBRARY_NAME} SDL2main.lib)

# C++/Compiler setting
set_property(TARGET ${ENGINE_LIBRARY_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${ENGINE_LIBRARY_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiless})

set_target_properties(
    ${ENGINE_LIBRARY_NAME}
    PROPERTIES OUTPUT_NAME 
    "SDLEngine"
)