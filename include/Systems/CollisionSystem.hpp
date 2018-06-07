//
// Created by NANAA on 07/06/18.
//

#ifndef INDIESTUDIO_COLLISIONSYSTEM_HPP
#define INDIESTUDIO_COLLISIONSYSTEM_HPP

#include <Interfaces/ISystem.hpp>
#include <GraphicalEngine.hpp>

class World;

namespace Systems {
	class CollisionSystem : public ISystem {
	public:
		CollisionSystem(GraphicalEngine *engine) : _engine(engine) {};

		void execute(World *ref) override;

	private:
		GraphicalEngine *_engine;
	};
}

#endif //INDIESTUDIO_COLLISIONSYSTEM_HPP
