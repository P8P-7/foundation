#pragma once

#include <CommandMessage.pb.h>
#include "repository.h"

namespace goliath::repositories {
    class PollingRepository : public Repository {
    public:
        virtual size_t getPollingCommandId() = 0;
        virtual std::vector<proto::CommandMessage> getCommandMessages();
    };
}