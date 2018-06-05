//
// Created by lucas on 05/06/2018.
//

#ifndef INDIESTUDIO_CONTROLLABLE_HPP
#define INDIESTUDIO_CONTROLLABLE_HPP

#include <string>
#include <iostream>
#include <irrlicht.h>
#include "IComponent.hpp"

namespace Components {
    class Controllable : public IComponent {
    public:
        Controllable() = default;
        ~Controllable() override = default;
        void summarize() const override {
            std::cout << "Controllable | Model : " << std::endl;
        };
        typeComponent getType() const override { return CONTROLLABLE; };

    public:
    };
}

#endif //INDIESTUDIO_CONTROLLABLE_HPP
