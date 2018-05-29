#pragma once

#include <string>
#include <repositories/ConfigRepository.pb.h>

#include "repository.h"

/**
 * @file config_repo.h
 * @author Group 7 - Informatica
 */

namespace goliath::repositories {
    class ConfigRepository : public Repository {
    public:
        explicit ConfigRepository(std::string &configFile);

        std::shared_ptr<::ConfigRepository> getConfig();
        std::unique_ptr<::google::protobuf::Message> getMessage() override;

    private:
        std::string jsonString;
    };
}