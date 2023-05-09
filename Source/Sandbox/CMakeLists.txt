INCLUDE_DIRECTORIES(${ENGINE_SRC_DIR})
INCLUDE_DIRECTORIES(${TP_SDL2_INCLUDE_DIR})

LINK_DIRECTORIES(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
LINK_DIRECTORIES(${TP_SDL2_LIB_DIR})

file(GLOB_RECURSE SourceFiles
${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

add_executable(Sandbox WIN32 ${SourceFiles})
target_link_libraries(Sandbox ${ENGINE_LIBRARY_NAME})
target_compile_features(Sandbox PRIVATE cxx_std_20)


# Need for fopen to use same path inside VS as executable inside /bin dir 
set_property(TARGET Sandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})

set(DLL_SOURCE_PATH "${TP_SDL2_LIB_DIR}/Debug/SDL2.dll")
set(DLL_DESTINATION_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)/SDL2.dll")

add_custom_command(
    TARGET Sandbox
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL_SOURCE_PATH}
        ${DLL_DESTINATION_PATH}
    COMMENT "Copying DLL to output directory"
)