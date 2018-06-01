/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef CPP_INDIE_STUDIO_ENTITY_HPP
#define CPP_INDIE_STUDIO_ENTITY_HPP

#include <cstdint>

struct EntityPosition
{
	uint32_t x;
	uint32_t y;
	uint32_t z;
};

enum EntityType
{
	WALL,
	GROUND,
	CHARACTER,
	BOMB
};

struct BaseEntity
{
	//CTOR
	BaseEntity(int64_t id, EntityType type, EntityPosition &position)
	: id(id), type(type), position(position) {};

	//FIELDS
	int64_t id;
	EntityType type;
	EntityPosition position;
};

#endif //CPP_INDIE_STUDIO_ENTITY_HPP
