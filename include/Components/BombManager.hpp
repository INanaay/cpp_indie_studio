//
// Created by clementbmn on 05/06/2018.
//

#ifndef INDIESTUDIO_BOMBMANAGER_HPP
#define INDIESTUDIO_BOMBMANAGER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <irrlicht.h>
#include <unordered_map>
#include "IComponent.hpp"

namespace Components {
    class BombManager : public IComponent {
    public:
        BombManager() : putBomb(false) {};
        ~BombManager() override = default;
        void summarize() const override {
            std::cout << "BombSystem " << std::endl;
        };
        typeComponent getType() const override { return BOMBMANAGER; };
        bool putBomb;
    };
}

#endif
