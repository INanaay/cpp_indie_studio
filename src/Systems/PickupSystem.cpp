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
			auto div = (playerPos.X) / 2.0f;
			auto round = (int) (truncf(div));
			float new_x;
			new_x = (float) round * 2.0f + (playerPos.X < 0.f ? -1.0f : 1.0f);
			div = (playerPos.Y) / 2.0f;
			round = (int) (truncf(div));
			float new_y;
			new_y = (float)round * 2.0f + (playerPos.Y < 0.f ? -1.0f : 1.0f);

			if (new_x == pickupPos.X && new_y == pickupPos.Y && pickupGraphical->node->isVisible())
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
						std::cout << "More bombs !" << std::endl;
                        (bombManager->availables)++;
						break;
				}


			}
		}
	}

}