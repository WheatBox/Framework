cmake_minimum_required(VERSION 3.14)

project(Framework)

include(utils.cmake)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/Third/)
set(THIRD_PARTY_PLATFORM_DIR "")

set(OUTPUT_DIR_DEBUG ${CMAKE_SOURCE_DIR}/Bin/Debug/)
set(OUTPUT_DIR_RELEASE ${CMAKE_SOURCE_DIR}/Bin/Release/)

find_package(glfw3 CONFIG REQUIRED)
find_package(Freetype CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED) # OpenAL-soft
find_package(SndFile CONFIG REQUIRED)

set(THIRD_LIBS
    glfw
    Freetype::Freetype
    OpenAL::OpenAL
    SndFile::sndfile
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR_DEBUG})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR_RELEASE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR_DEBUG})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR_RELEASE})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("GNU")
    add_compile_options(
        -Wall
        -Werror
        -Wno-switch
    )
endif()

if(MSVC)
    message("MSVC")
    add_compile_options(
        /utf-8
        /W4
        /WX
        /permissive
    )
endif()

AddFiles(CODE_FILES
    Framework
    Framework/FrameAsset
    Framework/FrameAudio
    Framework/FrameCore
    Framework/FrameEntity
    Framework/FrameInput
    Framework/FrameMath
    Framework/FrameReflection
    Framework/FrameRender
    Framework/FrameUtility

    Third/glad/src
)

AddFiles(SHADER_FILES
    Shaders
)

add_library(${CMAKE_PROJECT_NAME} SHARED
    ${CODE_FILES}
    ${SHADER_FILES}
    utils.cmake
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Framework/
    ${THIRD_PARTY_DIR}/glad/include/
    ${THIRD_PARTY_DIR}/stb/
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    ${THIRD_LIBS}
)

if(MSVC)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${OUTPUT_DIR_DEBUG},${OUTPUT_DIR_RELEASE}>"
    )
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
        VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME}
    )
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE FRAMEWORK_EXPORTS)
endif()

# Edit & Continue
if(MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC "/ZI")
    target_link_options(${CMAKE_PROJECT_NAME} PUBLIC "/INCREMENTAL")
endif()

add_subdirectory(Examples/Test)