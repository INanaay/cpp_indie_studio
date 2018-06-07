//
// Created by lucas on 05/06/2018.
//

#ifndef INDIESTUDIO_CONTROLLABLE_HPP
#define INDIESTUDIO_CONTROLLABLE_HPP

#include <string>
#include <iostream>
#include <irrlicht.h>
#include <unordered_map>
#include "IComponent.hpp"

enum CONTROL_ACTION {
    MOVEUP,
    MOVEDOWN,
    MOVELEFT,
    MOVERIGHT,
    NONE
};

using keymap = std::vector<std::pair<irr::EKEY_CODE, CONTROL_ACTION>>;

namespace Components {
    class Controllable : public IComponent {
    public:
        Controllable(keymap map) : _keymap(map) {};
        ~Controllable() override = default;
        void summarize() const override {
            std::cout << "Controllable | Model : " << std::endl;
        };
        typeComponent getType() const override { return CONTROLLABLE; };

    public:
        keymap _keymap;
    };
}

#endif //INDIESTUDIO_CONTROLLABLE_HPP
