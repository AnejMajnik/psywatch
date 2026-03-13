#pragma once
#include <deque>

namespace Util {

    template <typename T>
    void trim_usage_deque(std::deque<T> &usage) {
        while (usage.size() > 180) {
            usage.pop_front();
        }
    }
}