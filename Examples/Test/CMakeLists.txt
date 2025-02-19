cmake_minimum_required(VERSION 3.14)

project(Test)

include(../../utils.cmake)

set(CMAKE_CXX_STANDARD 17)

set(OUTPUT_DIR_DEBUG ${CMAKE_SOURCE_DIR}/Bin/Examples/${PROJECT_NAME}/Debug/)
set(OUTPUT_DIR_RELEASE ${CMAKE_SOURCE_DIR}/Bin/Examples/${PROJECT_NAME}/Release/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR_DEBUG})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR_DEBUG})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR_RELEASE})

CopyFilesToOutput(Assets)
CopyFilesToOutput(../../Shaders)

AddFiles(CODE_TEST_FILES
    Code
    Code/Components
)

add_executable(${PROJECT_NAME}
    ${CODE_TEST_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Framework/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Framework
)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=${CMAKE_SOURCE_DIR}/Bin/$<IF:$<CONFIG:Debug>,Debug,Release>;%PATH%")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${OUTPUT_DIR_DEBUG},${OUTPUT_DIR_RELEASE}>"
    )
    target_compile_options(${PROJECT_NAME} PUBLIC "/ZI")
    target_link_options(${PROJECT_NAME} PUBLIC "/INCREMENTAL")
endif()
