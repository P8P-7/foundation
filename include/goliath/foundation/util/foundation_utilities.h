#pragma once

#include <string>

/**
 * @file foundation_utilities.h
 * @author Group 7 - Informatica
 */

namespace goliath::util {
    class FoundationUtilities {
    public:
        static std::string executablePath(const std::string &executable);
        static std::string executableToFile(const std::string &executable, const std::string &file);

    };
}
