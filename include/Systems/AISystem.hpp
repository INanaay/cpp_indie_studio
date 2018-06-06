//
// Created by clementbmn on 05/06/2018.
//

#ifndef INDIESTUDIO_AISYSTEM_HPP
#define INDIESTUDIO_AISYSTEM_HPP

#include "ISystem.hpp"
#include "GraphicalEngine.hpp"

class World;

namespace Systems {

    class AISystem : public ISystem {
    public:
        AISystem(GraphicalEngine *engine) : _engine(engine) {};
        void execute(World *ref) override;

    private:
        GraphicalEngine *_engine;
    };
}

#endif
