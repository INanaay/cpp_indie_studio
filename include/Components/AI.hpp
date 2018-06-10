//
// Created by clementbmn on 05/06/2018.
//

#ifndef INDIESTUDIO_AI_HPP
#define INDIESTUDIO_AI_HPP

#include <cstdint>
#include <iostream>
#include "IComponent.hpp"
#include "Components.hpp"
#include "Controllable.hpp"

namespace Components {
    class AIComponent : public IComponent {
    public:
        AIComponent() : putBomb(false) {};
        ~AIComponent() override = default;
        void summarize() const override {std::cout << "AI" << std::endl;};
        typeComponent getType() const override { return AI; };
        bool putBomb;
        CONTROL_ACTION action;
    };
}


#endif
