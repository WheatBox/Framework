macro(CopyFilesToOutput _folderName)
	get_filename_component(_last_folder ${_folderName} NAME)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${_folderName}/ DESTINATION ${OUTPUT_DIR_DEBUG}/${_last_folder}/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${_folderName}/ DESTINATION ${OUTPUT_DIR_RELEASE}/${_last_folder}/)
endmacro(CopyFilesToOutput)

macro(AddFiles _dest)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	foreach(loop ${ARGV})
		string(REGEX REPLACE "/" "_" _filesvar ${loop})
		
		file(GLOB ${_filesvar} ./${loop}/*.*)
		source_group("${loop}" FILES ${${_filesvar}})

		string(APPEND ${_dest} "${${_filesvar}};")
	endforeach()

endmacro(AddFiles)
