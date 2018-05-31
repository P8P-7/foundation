#include <goliath/foundation/util/foundation_utilities.h>

using namespace goliath::util;

std::string FoundationUtilities::executablePath(const std::string &executable) {
    const unsigned long index = executable.find_last_of('/');
    if (std::string::npos != index) {
        return executable.substr(0, index + 1);
    }
    return executable;
}

std::string FoundationUtilities::executableToFile(const std::string &executable, const std::string &file) {
    return executablePath(executable) + file;
}
