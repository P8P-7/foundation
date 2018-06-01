set(RELATIVE_INCLUDES
        foundation.h
        foundation/repositories/proto_repository.h
        foundation/repositories/repository.h
        foundation/repositories/watcher.h
        foundation/util/console.h
        foundation/util/foundation_utilities.h
        foundation/handle.h
        foundation/handle_error.h
        foundation/publisher_service.h
        )

prepend(ABSOLUTE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR} ${RELATIVE_INCLUDES})

set(INCLUDES
        ${ABSOLUTE_INCLUDES}
        PARENT_SCOPE
        )
