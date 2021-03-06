//
// Created by lucas on 03/06/2018.
//

#ifndef INDIESTUDIO_SPEED_HPP
#define INDIESTUDIO_SPEED_HPP

#include <cstdint>
#include "IComponent.hpp"
#include <iostream>

namespace Components {
    class Velocity : public IComponent {
    public:
        Velocity(float vs) : value(vs), old_value(0.0f) {};
        ~Velocity() override = default;
        void summarize() const override {std::cout << "Velocity | Value : " << value << std::endl;};
        typeComponent getType() const override { return VELOCITY; };

    public:
        float value;
        float old_value;
        float baseVelocity = 10.f;
    };
}


#endif //INDIESTUDIO_SPEED_HPP
