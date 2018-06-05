//
// Created by lucas on 05/06/2018.
//

#ifndef INDIESTUDIO_CONTROLLABLESYSTEM_HPP
#define INDIESTUDIO_CONTROLLABLESYSTEM_HPP

#include "ISystem.hpp"

class World;

namespace Systems {

    class ControllableSystem : public ISystem {
    public:
        ControllableSystem(bool *keyDown) : _keyDown(keyDown) {};

        void execute(World *ref) override;

    private:
        bool *_keyDown;
    };
}


#endif //INDIESTUDIO_CONTROLLABLESYSTEM_HPP
