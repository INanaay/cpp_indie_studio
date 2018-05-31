/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include "../../include/game/GameManager.hpp"

GameManager::GameManager
(std::shared_ptr<Core> core, const std::vector<GameEntity> &entities)
{
	m_core = core;
	for (auto &entity: entities)
		m_entities[entity.id] = std::make_unique<GameEntity>(entity);
}
