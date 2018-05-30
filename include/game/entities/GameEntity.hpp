/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef CPP_INDIE_STUDIO_GAMEENTITY_HPP
#define CPP_INDIE_STUDIO_GAMEENTITY_HPP

#include "../../core/entities/BaseEntity.hpp"

class GameEntity : public BaseEntity
{
public:
	explicit GameEntity(uint64_t id, EntityType type, EntityPosition &position) : BaseEntity(id, type, position) {};
private:
};

#endif //CPP_INDIE_STUDIO_GAMEENTITY_HPP
