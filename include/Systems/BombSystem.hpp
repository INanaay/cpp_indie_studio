//
// Created by lucas on 03/06/2018.
//

#ifndef INDIESTUDIO_BOMBSYSTEM_HPP
#define INDIESTUDIO_BOMBSYSTEM_HPP

#include <iostream>
#include "ISystem.hpp"
#include "GraphicalEngine.hpp"
#include "Bomb.hpp"
#include "PhysicalBody.hpp"

class World;

namespace Systems {
	class BombSystem : public ISystem {
	public:
		BombSystem(GraphicalEngine *engine) : _engine(engine) {};
		void execute(World *ref) override;
		void explodeBomb(World *ref, Components::Bomb *&bomb, const uint32_t bomb_id, Components::PhysicalBody *&player);
	private:
		GraphicalEngine *_engine;
	};
}


#endif //INDIESTUDIO_DEMOSYSTEM_HPP
