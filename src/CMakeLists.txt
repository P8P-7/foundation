set(RELATIVE_SOURCES
        repositories/battery_repository.cpp
        repositories/config_repo.cpp
        repositories/watcher.cpp
        util/console.cpp
        util/foundation_utilities.cpp
        handle.cpp
        handle_error.cpp
        )

prepend(ABSOLUTE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} ${RELATIVE_SOURCES})

set(SOURCES
        ${ABSOLUTE_SOURCES}
        PARENT_SCOPE
        )
