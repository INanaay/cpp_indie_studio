//
// Created by clementbmn on 05/06/2018.
//

#ifndef INDIESTUDIO_TIMER_HPP
#define INDIESTUDIO_TIMER_HPP

#include <chrono>
#include <vector>
#include <string>
#include <iostream>
#include <irrlicht.h>
#include <unordered_map>
#include "IComponent.hpp"

namespace Components {
    class Timer : public IComponent {
    public:
        Timer() : _start(std::chrono::high_resolution_clock::now()) {};
        ~Timer() override = default;
        void summarize() const override {
            std::cout << "Timer " << std::endl;
        };
        typeComponent getType() const override { return TIMER; };
        std::chrono::time_point<std::chrono::system_clock> _start;
    };
}

#endif
