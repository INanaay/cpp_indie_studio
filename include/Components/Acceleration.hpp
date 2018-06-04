//
// Created by lucas on 03/06/2018.
//

#ifndef INDIESTUDIO_SPEED_HPP
#define INDIESTUDIO_SPEED_HPP

#include <cstdint>
#include "IComponent.hpp"

namespace Components {
    class Acceleration : public IComponent {
    public:
        Acceleration(uint32_t vs) : value(vs) {};
        ~Acceleration() override = default;
        void summarize() const override {std::cout << "Acceleration | Value : " << value << std::endl;};
        typeComponent getType() const override { return ACCELERATION; };

    public:
        uint32_t value;
    };
}


#endif //INDIESTUDIO_SPEED_HPP
