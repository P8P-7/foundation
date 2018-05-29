#include "handle.h"

#include <cstdlib>

#include "handle_error.h"

using namespace goliath::handles;

Handle::Handle(const size_t &handle_id)
    : id(handle_id) {
}

Handle::Handle(const Handle &other)
    : id(other.getId()), ownerId(other.ownerId) {
}

void Handle::lock(const size_t& commandId) {
    std::lock_guard<std::mutex> lock(mutex);
    if (isLocked()) {
        throw exceptions::HandleError(getId(), "Could not be locked because it was already in use.");
    }

    ownerId = commandId;
}

void Handle::unlock() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!isLocked()) {
        throw exceptions::HandleError(getId(), "Could not be unlocked because it wasn't locked.");
    }

    ownerId.reset();

    var.notify_one();
}

void Handle::waitAndLock(const size_t &commandId) {
    std::unique_lock<std::mutex> lock(mutex);
    var.wait(lock, [&]() { return !isLocked(); });

    ownerId = commandId;
}

const size_t Handle::getOwnerId() const {
    if(ownerId.is_initialized()) {
        return ownerId.get();
    }

    throw std::runtime_error("Owner is not set");
}

const size_t Handle::getId() const {
    return id;
}

bool Handle::isLocked() const {
    return ownerId.is_initialized();
}

bool Handle::isLocked(size_t ownerId) const {
    return isLocked() && getOwnerId() == ownerId;
}