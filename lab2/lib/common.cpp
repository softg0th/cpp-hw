#include <chrono>

std::string getCurrentTimeStamp () {
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
        now.time_since_epoch()).count();
    std::stringstream ss;
    ss << timestamp;
    return ss.str();
}