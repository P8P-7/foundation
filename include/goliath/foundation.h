#pragma once

/**
 * @file foundation.h
 * @author Group 7 - Informatica
 */

 /**
  * @namespace goliath::core
  * @brief Contains base-defenitions every module (and controller) needs
  */

#include "foundation/handle.h"
#include "foundation/handle_error.h"
#include "foundation/repositories/repository.h"
#include "foundation/repositories/proto_repository.h"
#include "foundation/repositories/config_repo.h"
#include "foundation/repositories/battery_repository.h"
#include "foundation/repositories/watcher.h"
#include "foundation/util/console.h"
#include "foundation/util/foundation_utilities.h"
#include "foundation/publisher_service.h"
