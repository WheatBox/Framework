cmake_minimum_required(VERSION 3.14)

project(Diary)

set(EXE_NAME Diary)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

option(Platform "The platform to compile to" "Windows-x64")
#	Platform can only be set to:
#		Windows-x64 (Default)
#		Windows-x86
#		Android (Haven't start yet)
#		iOS (Haven't start yet)

message("Platform = " ${Platform})

set(SDL_DIR "")
set(SDL_LIB_DIR "")
set(SDLTTF_DIR "")
set(SDLTTF_LIB_DIR "")

set(Windows-x64 NO)
set(Windows-x86 NO)

if(Platform STREQUAL "Windows-x64")

	set(Windows-x64 YES)

	set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Bin/Windows-x64/)

	set(SDL_DIR ${CMAKE_SOURCE_DIR}/Third/SDL2-devel-2.28.4-VC/)
	set(SDL_LIB_DIR ${SDL_DIR}/lib/x64/)

	set(SDLTTF_DIR ${CMAKE_SOURCE_DIR}/Third/SDL2_ttf-devel-2.20.2-VC/)
	set(SDLTTF_LIB_DIR ${SDLTTF_DIR}/lib/x64/)

	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		# 如果有需要的话，在这里设定 gcc/g++ 的编译器路径
		# Set gcc/g++ compiler path here if you need
		# set(CMAKE_C_COMPILER "F:/mingw64/bin/gcc")
		# set(CMAKE_CXX_COMPILER "F:/mingw64/bin/g++")
	endif()

elseif(Platform STREQUAL "Windows-x86")

	set(Windows-x86 YES)

	set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Bin/Windows-x86/)

	set(SDL_DIR ${CMAKE_SOURCE_DIR}/Third/SDL2-devel-2.28.4-VC/)
	set(SDL_LIB_DIR ${SDL_DIR}/lib/x86/)

	set(SDLTTF_DIR ${CMAKE_SOURCE_DIR}/Third/SDL2_ttf-devel-2.20.2-VC/)
	set(SDLTTF_LIB_DIR ${SDLTTF_DIR}/lib/x86/)

	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		# 如果有需要的话，在这里设定 gcc/g++ 的编译器路径
		# Set gcc/g++ compiler path here if you need
		set(CMAKE_C_COMPILER "F:/mingw32/bin/gcc")
		set(CMAKE_CXX_COMPILER "F:/mingw32/bin/g++")
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
message("SDL_DIR = " ${SDL_DIR})
message("SDL_LIB_DIR = " ${SDL_LIB_DIR})
message("SDLTTF_DIR = " ${SDLTTF_DIR})
message("SDLTTF_LIB_DIR = " ${SDLTTF_LIB_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${OUTPUT_DIR})

if(Windows-x64 OR Windows-x86)
	file(COPY ${SDL_LIB_DIR}/SDL2.dll DESTINATION ${OUTPUT_DIR})
	file(COPY ${SDLTTF_LIB_DIR}/SDL2_ttf.dll DESTINATION ${OUTPUT_DIR})
endif()

file(COPY ${CMAKE_SOURCE_DIR}/Assets/ DESTINATION ${OUTPUT_DIR}/Assets/)

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
	Code/Framework/FrameAsset
	Code/Framework/FrameCore
	Code/Framework/FrameEntity
	Code/Framework/FrameMath
	Code/Framework/FrameReflection
	Code/Framework/FrameRender
	Code/Framework/FrameUtility
)

AddFiles(ASSET_FILES
	Assets
	Assets/testfolder
)

add_executable(${EXE_NAME}
	${CODE_FILES}
	${ASSET_FILES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${SDL_DIR}/include/
	${SDLTTF_DIR}/include/
	${CMAKE_SOURCE_DIR}/Code/Framework/
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	${SDL_LIB_DIR}/SDL2main.lib
	${SDL_LIB_DIR}/SDL2.lib
	${SDLTTF_LIB_DIR}/SDL2_ttf.lib
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