
if(NOT EXISTS "${ASSET_SYMLINK_LOCATION}")
    message(STATUS "Creating symlink [${ASSET_SRC_LOCATION} <-> ${ASSET_SYMLINK_LOCATION}]")
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E create_symlink
            "${ASSET_SRC_LOCATION}"
            "${ASSET_SYMLINK_LOCATION}"
            RESULT_VARIABLE symlink_result
            ERROR_QUIET
    )

    if(NOT symlink_result EQUAL 0)
        message(WARNING "failed to create symlink [${ASSET_SRC_LOCATION} <-> ${ASSET_SYMLINK_LOCATION}], will perform a copy")
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${ASSET_SRC_LOCATION}"
                "${ASSET_SYMLINK_LOCATION}"
                RESULT_VARIABLE copy_result
                ERROR_QUIET
        )
        if(NOT copy_result EQUAL 0)
            message(FATAL_ERROR "failed to copy [${ASSET_SRC_LOCATION} <-> ${ASSET_SYMLINK_LOCATION}]...")
        else()
            message(STATUS "copy [${ASSET_SRC_LOCATION} <-> ${ASSET_SYMLINK_LOCATION}] completed successfully")
        endif()
    else()
        message(STATUS "symlink [${ASSET_SRC_LOCATION} <-> ${ASSET_SYMLINK_LOCATION}] created successfully")
    endif()
else()
    get_filename_component(actual_path "${ASSET_SYMLINK_LOCATION}" REALPATH)
    if(actual_path STREQUAL "${ASSET_SYMLINK_LOCATION}")
        # actual path, not symlink
        file(GLOB_RECURSE asset_files "${ASSET_SRC_LOCATION}/*")
        set(stale FALSE)
        foreach(asset_file ${asset_files})
            file(RELATIVE_PATH source_file "${ASSET_SRC_LOCATION}" "${asset_file}")
            set(dest_file "${ASSET_SYMLINK_LOCATION}/${source_file}")

            if(NOT EXISTS "${dest_file}")
                set(stale TRUE)
                break()
            else()
                file(TIMESTAMP "${source_file}" source_modified_time)
                file(TIMESTAMP "${dest_file}" dest_modified_time)
                if(source_modified_time STRGREATER dest_modified_time)
                    set(stale TRUE)
                    break()
                endif()
            endif()
        endforeach()

        if(stale)
            message(STATUS "detected modifications from source [${ASSET_SRC_LOCATION}], will update the copy at [${ASSET_SYMLINK_LOCATION}]...")
            execute_process(
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${ASSET_SRC_LOCATION}"
                    "${ASSET_SYMLINK_LOCATION}"
                    RESULT_VARIABLE copy_result
                    ERROR_QUIET
            )
        else()
            message(STATUS "[${ASSET_SYMLINK_LOCATION}] is up-to-date.")
        endif()
    else()
        message(STATUS "[${ASSET_SYMLINK_LOCATION}] is up-to-date.")
    endif()
endif()
