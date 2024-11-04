cmake_minimum_required(VERSION 3.14)

project(Framework)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

option(Platform "The platform to compile to" "Windows-x64")

set(PlatformNote "#
#	Platform can only be set to:
#		Windows-x64 (Default)
#		Windows-x86 (In Progress)
#		Linux
#		Android (Haven't start yet)
#		iOS (Haven't start yet)
#")

message("Platform = " ${Platform})

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/Third/)
set(THIRD_PARTY_PLATFORM_DIR "")

set(Windows-x64 NO)
set(Windows-x86 NO)
set(Linux NO)

if(Platform STREQUAL "Windows-x64")

	set(Windows-x64 YES)

	set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Bin/Windows-x64/)
	set(THIRD_PARTY_PLATFORM_DIR ${THIRD_PARTY_DIR}/Windows/)

elseif(Platform STREQUAL "Windows-x86")

	set(Windows-x86 YES)

	set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Bin/Windows-x86/)

elseif(Platform STREQUAL "Linux")

	set(Linux YES)

	set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Bin/Linux/)

else()
	message(FATAL_ERROR "
# ------------------------------------------------ #
#
#	FATAL ERROR : Unknown Platform
"
${PlatformNote}
"
# ------------------------------------------------ #
")
endif()

find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenAL REQUIRED) # OpenAL-soft
find_package(SndFile REQUIRED)

set(OUTPUT_LIB_DIR ${CMAKE_SOURCE_DIR}/Bin/Lib/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${OUTPUT_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

if(Windows-x64)
	file(COPY ${SNDFILE_DIR}/bin/sndfile.dll DESTINATION ${OUTPUT_DIR})

	file(COPY ${OPENAL_DIR}/bin/Win64/soft_oal.dll DESTINATION ${OUTPUT_DIR})
	file(RENAME ${OUTPUT_DIR}/soft_oal.dll ${OUTPUT_DIR}/OpenAL32.dll)
elseif(Windows-x86)
endif()

macro(CopyFilesToOutput _folderName)

	file(COPY ${CMAKE_SOURCE_DIR}/${_folderName}/ DESTINATION ${OUTPUT_DIR}/${_folderName}/)

endmacro(CopyFilesToOutput)

CopyFilesToOutput(Assets)
CopyFilesToOutput(Shaders)

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

macro(AddFiles _dest)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	foreach(loop ${ARGV})
		string(REGEX REPLACE "/" "_" _filesvar ${loop})
		
		file(GLOB ${_filesvar} ./${loop}/*.*)
		source_group("${loop}" FILES ${${_filesvar}})

		string(APPEND ${_dest} "${${_filesvar}};")
	endforeach()

endmacro(AddFiles)

AddFiles(CODE_FILES
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
	
	Third/glad/src
)

AddFiles(CODE_TEST_FILES
	Code
	Code/Diary
	Code/Diary/Components
)

AddFiles(ASSET_FILES
	Assets
	Assets/testfolder
)

AddFiles(SHADER_FILES
	Shaders
)

add_library(${CMAKE_PROJECT_NAME} STATIC
	${CODE_FILES}
	${SHADER_FILES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/Code/Framework/

	${THIRD_PARTY_DIR}/glad/include/
	${THIRD_PARTY_DIR}/stb/
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	glfw
	Freetype::Freetype
	OpenAL::OpenAL
	SndFile::sndfile
)

if(MSVC)
	set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY ${OUTPUT_DIR}
	)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
		VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME}
	)
endif()

# - Test --------------------

add_executable(Test
	${CODE_TEST_FILES}
	${ASSET_FILES}
)

target_include_directories(Test PRIVATE
	${CMAKE_SOURCE_DIR}/Code/Framework/
)

target_link_libraries(Test PRIVATE
	${CMAKE_PROJECT_NAME}
)

if(MSVC)
	set_target_properties(Test PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY ${OUTPUT_DIR}
	)
endif()

# ---------------------------

# Edit & Continue
if(MSVC)
	target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC "/ZI")
	target_link_options(${CMAKE_PROJECT_NAME} PUBLIC "/INCREMENTAL")
endif()
