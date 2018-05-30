/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include <cstdint>
#include "GraphicalEntity.hpp"

GraphicalEntity::GraphicalEntity (int64_t id, EntityType type, EntityPosition &position, irr::scene::IAnimatedMeshSceneNode *node)
: BaseEntity(id, type, position), node(node), status(GraphicalEntityStatus::IDLE)
{

}
