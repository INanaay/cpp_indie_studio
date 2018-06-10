//
// Created by NANAA on 10/06/18.
//

#include "World.hpp"
#include "Components.hpp"
#include <Systems/PickupSystem.hpp>
#include <Pickup.hpp>

void Systems::PickupSystem::execute(World *ref)
{
	auto players = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, PLAYERCOLLISION});
	auto pickups = ref->getComponentManager().getEntityByComponents({PHYSICALBODY, GRAPHICALBODY, PICKUP});

	for (auto &player : players)
	{
		auto playerGraphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(
			player, GRAPHICALBODY);
		for (auto &pickup : pickups)
		{
			const auto playerPos = playerGraphical->node->getPosition();
			auto pickupGraphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(
				pickup, GRAPHICALBODY);
			const auto pickupPos = pickupGraphical->node->getPosition();
			const auto pickupCmpt = ref->getComponentManager().getComponent<Components::Pickup>(
				pickup, PICKUP);;

			if (round(playerPos.X) == round(pickupPos.X) && round(playerPos.Y) == round(pickupPos.Y) && pickupGraphical->node->isVisible())
			{
				std::cout << "player picked up pickup\n";
				pickupGraphical->node->setVisible(false);
				switch (pickupCmpt->pickupType)
				{
					case SPEEDPICKUP :
						break;
					case RADIUSPICKUP:
						break;
					case BOMBPICKUP:
						auto bombManager = ref->getComponentManager().getComponent<Components::BombManager>(player, BOMBMANAGER);
						bombManager->availables++;
						break;
				}


			}
		}
	}

}