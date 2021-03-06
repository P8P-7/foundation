#pragma once

#include <MessageCarrier.pb.h>

/**
 * @file publisher_service.h
 * @author Group 7 - Informatica
 */


namespace goliath::foundation {
    class PublisherService {
    public:
        /**
         * @param carrier message to send
         * @return true if the carrier has successfully been sent to the publisher
         */
        virtual bool publish(const proto::MessageCarrier& carrier) = 0;
    };
}
