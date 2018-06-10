//
// Created by clementbmn on 05/06/2018.
//

#ifndef INDIESTUDIO_AI_HPP
#define INDIESTUDIO_AI_HPP

#include <cstdint>
#include <iostream>
#include "IComponent.hpp"

namespace Components {
    class AIComponent : public IComponent {
    public:
        AIComponent() {};
        ~AIComponent() override = default;
        void summarize() const override {std::cout << "AI" << std::endl;};
        typeComponent getType() const override { return AI; };
    };
}


#endif
