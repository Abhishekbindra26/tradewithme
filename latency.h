#pragma once
#include <chrono>
#include <string>

class Latency{
    public:
    static std::chrono::high_resolution_clock::time_point start();
    static void end(const std::chrono::high_resolution_clock::time_point& start_time, const std::string& action_name);
};