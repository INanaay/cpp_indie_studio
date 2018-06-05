//
// Created by lucas on 03/06/2018.
//

#ifndef INDIESTUDIO_SPEED_HPP
#define INDIESTUDIO_SPEED_HPP

#include <cstdint>
#include "IComponent.hpp"

namespace Components {
    class Velocity : public IComponent {
    public:
        Velocity(uint32_t vs) : value(vs) {};
        ~Velocity() override = default;
        void summarize() const override {std::cout << "Velocity | Value : " << value << std::endl;};
        typeComponent getType() const override { return VELOCITY; };

    public:
        uint32_t value;
    };
}


#endif //INDIESTUDIO_SPEED_HPP
