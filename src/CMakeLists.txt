set(RELATIVE_SOURCES
        repositories/repository.cpp
        repositories/polling_repository.cpp
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
