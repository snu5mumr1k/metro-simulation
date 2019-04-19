#pragma once

namespace util {
template<typename T>
T* Singleton() {
    static T instance;
    return &instance;
}
}  // namespace util
