/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/06 by cjdcoy
*/

#ifndef INDIESTUDIO_MOVEMENTSYSTEM_HPP
#define INDIESTUDIO_MOVEMENTSYSTEM_HPP

#include "ISystem.hpp"
#include "PhysicalBody.hpp"
#include "GraphicalEngine.hpp"

class World;

namespace Systems {

	class MovementSystem : public ISystem {
	public:
		MovementSystem(GraphicalEngine *engine) : _engine(engine) {};

		void execute(World *ref) override;
	private:
		GraphicalEngine *_engine;
	};
}

#endif //INDIESTUDIO_MOVEMENTSYSTEM_HPP
