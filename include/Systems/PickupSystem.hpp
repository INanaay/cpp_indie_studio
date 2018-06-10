//
// Created by NANAA on 10/06/18.
//

#ifndef INDIESTUDIO_PICKUPSYSTEM_HPP
#define INDIESTUDIO_PICKUPSYSTEM_HPP

#include <Interfaces/ISystem.hpp>
#include <GraphicalEngine.hpp>

class World;

namespace Systems {
	class PickupSystem : public ISystem {
	public:
		PickupSystem(GraphicalEngine *engine) : _engine(engine) {};

		void execute(World *ref) override;

	private:
		GraphicalEngine *_engine;
		void addSpeed(Components::PhysicalBody *physicalBody);
	};
}

#endif //INDIESTUDIO_PICKUPSYSTEM_HPP
