//
// Created by NANAA on 07/06/18.
//

#include <Systems/CollisionSystem.hpp>
#include <WallCollision.hpp>
#include <GraphicalBody.hpp>
#include <PlayerCollision.hpp>
#include <mutex>
#include "World.hpp"


extern std::mutex positionComponentMutex;

void Systems::CollisionSystem::execute(World *ref)
{
		auto wallEntities = ref->getComponentManager().getEntityByComponents({WALLCOLLISION});

		for (const auto &entityID : wallEntities)
		{
			auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(entityID, GRAPHICALBODY);
			auto collision = ref->getComponentManager().getComponent<Components::WallCollision>(entityID, WALLCOLLISION);
			if (graphical->isLoaded && !collision->isLoaded)
			{
				collision->selector = _engine->getScene()->createOctTreeTriangleSelector(graphical->mesh, graphical->node
				);
				graphical->node->setTriangleSelector(collision->selector);
				_engine->getMetaSelector()->addTriangleSelector(collision->selector);
				collision->isLoaded = true;
			}

		}

		auto playerEntities = ref->getComponentManager().getEntityByComponents({PLAYERCOLLISION});
		irr::core::vector3df hitbox(0.5, 0.5, 0.5);


		for (const auto &entityID : playerEntities)
		{
			auto collision = ref->getComponentManager().getComponent<Components::PlayerCollision>(entityID, PLAYERCOLLISION);
			auto graphical = ref->getComponentManager().getComponent<Components::GraphicalBody>(entityID, GRAPHICALBODY);
			if (graphical->isLoaded && !collision->isLoaded)
			{
				auto node = graphical->node;
				collision->anim = _engine->getScene()->createCollisionResponseAnimator
					(_engine->getMetaSelector(), node,
					 (hitbox),
					 irr::core::vector3df(0, 0, 0));
				node->addAnimator(collision->anim);
				collision->anim->drop();
				collision->isLoaded = true;
			}
		}
}