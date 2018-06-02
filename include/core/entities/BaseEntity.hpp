/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef CPP_INDIE_STUDIO_ENTITY_HPP
#define CPP_INDIE_STUDIO_ENTITY_HPP

#include <cstdint>
#include <irrlicht.h>

using Node = irr::scene::IAnimatedMeshSceneNode *;

struct EntityPosition
{
	uint32_t x;
	uint32_t y;
	uint32_t z;
};

struct BaseEntity
{
	//CTOR
	BaseEntity(EntityPosition &position) : position(position), node(nullptr) {};

	//FIELDS
	EntityPosition position;
	Node node;
};

#endif //CPP_INDIE_STUDIO_ENTITY_HPP
