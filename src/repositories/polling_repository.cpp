#include <goliath/foundation/repositories/polling_repository.h>

using namespace goliath::repositories;

std::vector<goliath::proto::CommandMessage> PollingRepository::getCommandMessages() {
    goliath::proto::CommandMessage emptyMessage;
    return {{emptyMessage}};
}