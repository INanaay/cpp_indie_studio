//
// Created by NANAA on 13/06/18.
//

#include "Components.hpp"
#include "World.hpp"
#include <Systems/RulesCheckerSystem.hpp>


void Systems::RulesCheckerSystem::execute(World *ref)
{
	bool result = false;

	if (_nbPlayers == 1)
	{
		result = checkOnePlayer(ref);
	}
	else if (_nbPlayers == 2)
	{
		result = checkTwoPlayers(ref);
	}

	if (result)
	{
		_engine->getDevice()->closeDevice();
	}
}

bool Systems::RulesCheckerSystem::checkOnePlayer(World *ref)
{
	auto player = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, PLAYER});

	for (const auto &pl : player) {
		auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(pl, GRAPHICALBODY);

		if (!graphical->node->isVisible()) {
			std::cout << "You lose" << std::endl;
			return true;
		}
	}

	auto ais = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, AI});

	for (const auto &ai : ais)
	{
		auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(ai, GRAPHICALBODY);

		if (graphical->node->isVisible())
			return false;

	}
	std::cout << "You win" << std::endl;

	return true;
}

bool Systems::RulesCheckerSystem::checkTwoPlayers(World *ref) {
	auto players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, PLAYER});
	int nbPlayersDead = 0;
	int nbAiDead = 0;


	for (const auto &player : players) {
		auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(player,
												    GRAPHICALBODY);

		if (!graphical->node->isVisible())
			nbPlayersDead++;
	}


	auto ais = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, AI});

	for (const auto &ai : ais) {
		auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(ai, GRAPHICALBODY);

		if (!graphical->node->isVisible())
			nbAiDead++;
	}
	if (nbAiDead == 2 && nbPlayersDead == 1) {
		std::cout << "You win" << std::endl;
		return true;
	}
	if (nbAiDead == 2 && nbPlayersDead == 2) {
		std::cout << "Tie" << std::endl;

		return true;
	}
	if (nbPlayersDead == 2) {
		std::cout << "You lose" << std::endl;
		return true;
	}
	return false;
}
