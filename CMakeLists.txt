cmake_minimum_required(VERSION 3.14)

project(Framework)

set(EXE_NAME Framework)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

option(Platform "The platform to compile to" "Windows-x64")
#	Platform can only be set to:
#		Windows-x64 (Default)
#		Windows-x86
#		Android (Haven't start yet)
#		iOS (Haven't start yet)

message("Platform = " ${Platform})

set(GLFW_DIR "")
set(GLFW_LIB_DIR "")
set(FREETYPE_DIR "")
set(FREETYPE_LIB_DIR "")

set(Windows-x64 NO)
set(Windows-x86 NO)

if(Platform STREQUAL "Windows-x64")

	set(Windows-x64 YES)

	set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Bin/Windows-x64/)

	set(GLFW_DIR ${CMAKE_SOURCE_DIR}/Third/glfw-3.3.8.bin.WIN64/)
	set(GLFW_LIB_DIR ${GLFW_DIR}/lib-vc2022/)
	set(FREETYPE_DIR ${CMAKE_SOURCE_DIR}/Third/freetype-windows-binaries-2.13.2/)
	set(FREETYPE_LIB_DIR "${FREETYPE_DIR}/release static/vs2015-2022/win64/")

	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		# 如果有需要的话，在这里设定 gcc/g++ 的编译器路径
		# Set gcc/g++ compiler path here if you need
		# set(CMAKE_C_COMPILER "F:/mingw64/bin/gcc")
		# set(CMAKE_CXX_COMPILER "F:/mingw64/bin/g++")

		# TODO - set(GLFW_LIB_DIR ${GLFW_DIR}/lib-TODO/)
		message("TODO")
	endif()

elseif(Platform STREQUAL "Windows-x86")

	set(Windows-x86 YES)

	set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Bin/Windows-x86/)

	# TODO
	message("TODO")

	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		# 如果有需要的话，在这里设定 gcc/g++ 的编译器路径
		# Set gcc/g++ compiler path here if you need
		set(CMAKE_C_COMPILER "F:/mingw32/bin/gcc")
		set(CMAKE_CXX_COMPILER "F:/mingw32/bin/g++")

		# TODO
		message("TODO")
	endif()

else()
	message(FATAL_ERROR "
# ------------------------------------------------ #
#
#	FATAL ERROR : Unknown Platform
#
#	Platform can only be set to:
#		Windows-x64 (Default)
#		Windows-x86
#		Android (Haven't start yet)
#		iOS (Haven't start yet)
#
# ------------------------------------------------ #
")
endif()

message("OUTPUT_DIR = " ${OUTPUT_DIR})
message("GLFW_DIR = " ${GLFW_DIR})
message("GLFW_LIB_DIR = " ${GLFW_LIB_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${OUTPUT_DIR})

if(Windows-x64)
	#file(COPY if_we_need.dll DESTINATION ${OUTPUT_DIR})
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
	)
endif()

if(MSVC)
	message("MSVC")
	add_compile_options(
		/utf-8
		/W4
		/WX
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
	Code
	Code/Diary
	Code/Diary/Components
	Code/Framework
	Code/Framework/FrameAsset
	Code/Framework/FrameCore
	Code/Framework/FrameEntity
	Code/Framework/FrameInput
	Code/Framework/FrameMath
	Code/Framework/FrameReflection
	Code/Framework/FrameRender
	Code/Framework/FrameUtility
	
	Third/glad/src
)

AddFiles(ASSET_FILES
	Assets
	Assets/testfolder
)

AddFiles(SHADER_FILES
	Shaders
)

add_executable(${EXE_NAME}
	${CODE_FILES}
	${ASSET_FILES}
	${SHADER_FILES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${GLFW_DIR}/include/
	${FREETYPE_DIR}/include/
	${CMAKE_SOURCE_DIR}/Code/Framework/
	${CMAKE_SOURCE_DIR}/Third/glad/include/
	${CMAKE_SOURCE_DIR}/Third/stb/
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	${GLFW_LIB_DIR}/glfw3.lib
	${FREETYPE_LIB_DIR}/freetype.lib
)

if(MSVC)
	set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY ${OUTPUT_DIR}
	)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
		VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME}
	)
endif()

# Edit & Continue
if(MSVC)
	target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC "/ZI")
	target_link_options(${CMAKE_PROJECT_NAME} PUBLIC "/INCREMENTAL")
endif()