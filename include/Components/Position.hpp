//
// Created by lucas on 03/06/2018.
//

#ifndef INDIESTUDIO_POSITION_HPP
#define INDIESTUDIO_POSITION_HPP

#include <cstdint>
#include "IComponent.hpp"

namespace Components {
    class Position : public IComponent {
    public:
        Position(uint32_t xs, uint32_t ys, uint32_t zs) : x(xs), y(ys), z(zs) {};
        ~Position() override = default;
        void summarize() const override {std::cout << "Position | X : " << x << " | Y : " << y << " | Z : " << z << std::endl;};
        typeComponent getType() const override { return POSITION; };

    public:
        uint32_t x;
        uint32_t y;
        uint32_t z;
    };
}

#endif //INDIESTUDIO_POSITION_HPP
