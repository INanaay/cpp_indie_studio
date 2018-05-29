/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef CPP_INDIE_STUDIO_GRAPHICALENTITY_HPP
#define CPP_INDIE_STUDIO_GRAPHICALENTITY_HPP

#include <IAnimatedMeshSceneNode.h>
#include "../../core/entities/BaseEntity.hpp"

enum GraphicalEntityStatus
{
	IDLE,
	DYING,
	MOVING,
};


struct GraphicalEntity : public BaseEntity
{
	//CTOR
	GraphicalEntity
	(int64_t id, EntityType type, EntityPosition &position, irr::scene::IAnimatedMeshSceneNode *node);

	GraphicalEntityStatus status;
	irr::scene::IAnimatedMeshSceneNode *node;
};

#endif //CPP_INDIE_STUDIO_GRAPHICALENTITY_HPP
