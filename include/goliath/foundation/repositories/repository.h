#pragma once

#include <google/protobuf/message.h>

#include <atomic>

/**
 * @file repository.h
 * @author Group 7 - Informatica
 */

namespace goliath::repositories {
    /**
     * @class goliath::repositories::Repository
     * @brief Repository base class
     */
    class Repository {
    public:
        /**
         * @brief Compiles the fields of this repository to an instance of <a href="https://developers.google.com/protocol-buffers/docs/reference/cpp/google.protobuf.message">Message</a>
         * @return instance of <a href="https://developers.google.com/protocol-buffers/docs/reference/cpp/google.protobuf.message">Message</a> with all information
         */
        virtual std::unique_ptr<::google::protobuf::Message> getMessage() = 0;

        /**
         * @return true if this repository has been changed
         */
        virtual bool isInvalidated() const;

        /**
         * @brief Forces the repository to be synchronized
         */
        void invalidate();

    private:
        friend class Watcher;

        void validate();

        std::atomic<bool> invalidated{false};
    };
}
