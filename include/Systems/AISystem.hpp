//
// Created by clementbmn on 05/06/2018.
//

#ifndef INDIESTUDIO_AISYSTEM_HPP
#define INDIESTUDIO_AISYSTEM_HPP

#include <vector>
#include "ISystem.hpp"
#include "GraphicalEngine.hpp"

class World;

namespace Systems {

    class AISystem : public ISystem {
    public:
        AISystem(GraphicalEngine *engine, std::vector<std::vector<unsigned char>> map) :
                _engine(engine), _map(map) {};
        std::vector<std::vector<unsigned char>> getMap(World *ref);
        void execute(World *ref) override;

    private:
        GraphicalEngine *_engine;
        std::vector<std::vector<unsigned char>> _map;
    };
}

#endif
