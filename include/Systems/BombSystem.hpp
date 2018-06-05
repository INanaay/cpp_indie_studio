//
// Created by lucas on 03/06/2018.
//

#ifndef INDIESTUDIO_DEMOSYSTEM_HPP
#define INDIESTUDIO_DEMOSYSTEM_HPP

#include <iostream>
#include "GraphicalEngine.hpp"
#include "ISystem.hpp"

class World;

namespace Systems {
	class BombSystem : public ISystem {
	public:
		BombSystem(GraphicalEngine *engine) : _engine(engine) {};
		void execute(World *ref) override;
	private:
		GraphicalEngine *_engine;
	};
}


#endif //INDIESTUDIO_DEMOSYSTEM_HPP
