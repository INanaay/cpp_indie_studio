//
// Created by lucas on 03/06/2018.
//

#ifndef INDIESTUDIO_BOMBSYSTEM_HPP
#define INDIESTUDIO_BOMBSYSTEM_HPP

#include <iostream>
#include <GraphicalBody.hpp>
#include "ISystem.hpp"
#include "GraphicalEngine.hpp"
#include "PhysicalBody.hpp"
#include "Timer.hpp"

class World;

namespace Systems {
	class BombSystem : public ISystem {
	public:
		BombSystem(GraphicalEngine *engine) : _engine(engine) {};
		void execute(World *ref) override;
        void explodeBomb(World *ref, const uint32_t &bomb, Components::GraphicalBody *&bombGraphical,
        Components::PhysicalBody *&bombPhysical, Components::Timer *&timer);
            private:
		GraphicalEngine *_engine;
	};
}


#endif //INDIESTUDIO_DEMOSYSTEM_HPP
