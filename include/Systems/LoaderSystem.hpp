//
// Created by lucas on 04/06/2018.
//

#ifndef INDIESTUDIO_LOADERSYSTEM_HPP
#define INDIESTUDIO_LOADERSYSTEM_HPP

#include "ISystem.hpp"
#include "GraphicalEngine.hpp"

class World;

namespace Systems {

    class LoaderSystem : public ISystem {
    public:
        LoaderSystem(GraphicalEngine *engine) : _engine(engine) {};

        void execute(World *ref) override;

    private:
        GraphicalEngine *_engine;
    };
}

#endif //INDIESTUDIO_LOADERSYSTEM_HPP
