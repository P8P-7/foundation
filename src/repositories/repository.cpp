#include <goliath/foundation/repositories/repository.h>

using namespace goliath::repositories;

bool Repository::isInvalidated() const {
    return invalidated;
}

void Repository::invalidate() {
    invalidated = true;
}

void Repository::validate() {
    invalidated = false;
}