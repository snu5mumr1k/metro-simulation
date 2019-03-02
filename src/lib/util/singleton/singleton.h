#pragma once

template<typename T>
T* Singleton() {
    static T instance;
    return &instance;
}
