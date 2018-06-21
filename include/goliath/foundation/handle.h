#pragma once

#include <mutex>
#include <condition_variable>
#include <boost/optional.hpp>

/**
 * @file handle.h
 * @author Group 7 - Informatica
 */

namespace goliath::handles {
    class Handle {
    public:
        explicit Handle(const size_t &handleId);
        Handle(const Handle &other);

        /**
         * @brief Lock the handle.
         * @param commandId the owning command @headerfile handle.h
         */
        void lock(const size_t &commandId);

        /**
         * @brief Release the handle.
         */
        void unlock();

        /**
         * @brief Wait for the lock to become available and acquire the lock.
         * @param commandId the owning command @headerfile handle.h
         */
        void waitAndLock(const size_t &commandId);

        /**
         * @return command id of owning command in @headerfile handle.h
         */
        const size_t getOwnerId();

        /**
         * @return handle id as registered
         */
        const size_t getId() const;

        /**
         * @brief Indicates whether or not this handle has been locked.
         * @return true if this handle has been locked
         */
        bool isLocked();

        /**
         * @brief Checks if this handle is locked for a specific owner
         * @param ownerId owner to check for
         * @return true if this handle is locked for ownerId
         */
        bool isLocked(size_t ownerId);
    private:
        const size_t id;

        boost::optional<size_t> ownerId;
        std::mutex mutex;
        std::condition_variable var;
    };
}
