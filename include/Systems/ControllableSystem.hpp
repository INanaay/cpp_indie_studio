//
// Created by lucas on 05/06/2018.
//

#ifndef INDIESTUDIO_CONTROLLABLESYSTEM_HPP
#define INDIESTUDIO_CONTROLLABLESYSTEM_HPP

#include "ISystem.hpp"
#include "Components.hpp"
#include "GraphicalEngine.hpp"

class World;

namespace Systems {

    class ControllableSystem : public ISystem {
    public:
        ControllableSystem(GraphicalEngine *engine, bool *keyDown) : _keyDown(keyDown), _engine(engine) {};

        void disableAction(CONTROL_ACTION, Components::PhysicalBody *, Components::Velocity *,
                           Components::BombManager *);
        void enableAction(World *ref, CONTROL_ACTION, Components::PhysicalBody *, Components::Velocity *,
                          Components::BombManager *bombManager, uint32_t id);
        void execute(World *ref) override;

    private:
        bool *_keyDown;
        GraphicalEngine *_engine;
        CONTROL_ACTION _lastAction;
    };
}


#endif //INDIESTUDIO_CONTROLLABLESYSTEM_HPP
