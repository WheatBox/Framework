cmake_minimum_required(VERSION 3.14)

project(Framework)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# set(VCPKG_DEFAULT_LIBRARY_LINKAGE static)

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/Third/)
set(THIRD_PARTY_PLATFORM_DIR "")

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Bin/Test/)

find_package(glfw3 CONFIG REQUIRED)
find_package(Freetype CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED) # OpenAL-soft
find_package(SndFile CONFIG REQUIRED)

set(THIRD_LIBS glfw Freetype::Freetype OpenAL::OpenAL SndFile::sndfile)

set(OUTPUT_LIB_DIR ${CMAKE_SOURCE_DIR}/Bin/Lib/)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${OUTPUT_DIR})

macro(CopyFilesToOutput _folderName)

  file(COPY ${CMAKE_SOURCE_DIR}/${_folderName}/
       DESTINATION ${OUTPUT_DIR}/${_folderName}/)

endmacro(CopyFilesToOutput)

copyfilestooutput(Assets)
copyfilestooutput(Shaders)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message("GNU")
  add_compile_options(-Wall -Werror -Wno-switch -static)
endif()

if(MSVC)
  message("MSVC")
  add_compile_options(/utf-8 /W4 /WX /permissive $<$<CONFIG:Debug>:/MTd>
                      $<$<CONFIG:Release>:/MT>)
  # set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

macro(AddFiles _dest)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  foreach(loop ${ARGV})
    string(REGEX REPLACE "/" "_" _filesvar ${loop})

    file(GLOB ${_filesvar} ./${loop}/*.*)
    source_group("${loop}" FILES ${${_filesvar}})

    string(APPEND ${_dest} "${${_filesvar}};")
  endforeach()

endmacro(AddFiles)

addfiles(
  CODE_FILES
  Code/Framework
  Code/Framework/FrameAsset
  Code/Framework/FrameAudio
  Code/Framework/FrameCore
  Code/Framework/FrameEntity
  Code/Framework/FrameInput
  Code/Framework/FrameMath
  Code/Framework/FrameReflection
  Code/Framework/FrameRender
  Code/Framework/FrameUtility
  Third/glad/src)

addfiles(CODE_TEST_FILES Code Code/Diary Code/Diary/Components)

addfiles(ASSET_FILES Assets Assets/testfolder)

addfiles(SHADER_FILES Shaders)

add_library(${CMAKE_PROJECT_NAME} STATIC ${CODE_FILES} ${SHADER_FILES})

target_include_directories(
  ${CMAKE_PROJECT_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}/Code/Framework/ ${THIRD_PARTY_DIR}/glad/include/
          ${THIRD_PARTY_DIR}/stb/)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${THIRD_LIBS})

if(MSVC)
  set_target_properties(${CMAKE_PROJECT_NAME}
                        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${OUTPUT_DIR})
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
               PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})
endif()

# * Test --------------------

add_executable(Test ${CODE_TEST_FILES} ${ASSET_FILES})

target_include_directories(Test PRIVATE ${CMAKE_SOURCE_DIR}/Code/Framework/)

target_link_libraries(Test PRIVATE ${CMAKE_PROJECT_NAME})

if(MSVC)
  set_target_properties(Test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
                                        ${OUTPUT_DIR})
  target_compile_options(Test PUBLIC "/ZI")
  target_link_options(Test PUBLIC "/INCREMENTAL")
endif()

# ---------------------------

# Edit & Continue
if(MSVC)
  target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC "/ZI")
  target_link_options(${CMAKE_PROJECT_NAME} PUBLIC "/INCREMENTAL")
endif()
