
if(NOT EXISTS "${ASSET_SYMLINK_LOCATION}")
    message(STATUS "Creating symlink [${ASSET_DIR} <-> ${ASSET_SYMLINK_LOCATION}]")
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E create_symlink
            "${ASSET_DIR}"
            "${ASSET_SYMLINK_LOCATION}"
            RESULT_VARIABLE result
            ERROR_QUIET
    )

    if(NOT result EQUAL 0)
        message(WARNING "failed to create symlink [${ASSET_DIR} <-> ${ASSET_SYMLINK_LOCATION}], will perform a copy")
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${ASSET_DIR}"
                "${ASSET_SYMLINK_LOCATION}"
                RESULT_VARIABLE result
                ERROR_QUIET
        )
        if(NOT RESULT EQUAL 0)
            message(WARNING "failed to copy [${ASSET_DIR} <-> ${ASSET_SYMLINK_LOCATION}]...")
        else()
            message(STATUS "copy [${ASSET_DIR} <-> ${ASSET_SYMLINK_LOCATION}] completed successfully")
        endif()
    else()
        message(STATUS "symlink [${ASSET_DIR} <-> ${ASSET_SYMLINK_LOCATION}] created successfully")
    endif()
else()
    message(STATUS "symlink [${ASSET_DIR} <-> ${ASSET_SYMLINK_LOCATION}] already exists, skipping...")
endif()
