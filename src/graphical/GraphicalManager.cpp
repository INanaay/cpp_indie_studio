/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include <vector>
#include <GraphicalEntity.hpp>
#include <GraphicalManager.hpp>

//CTOR
GraphicalManager::GraphicalManager
(Core &core, const std::vector<GraphicalEntity> &entities)
{
	m_core = &core;
	for (auto &entity: entities)
		m_entities[entity.id] = std::make_unique<GraphicalEntity>(entity);
}

//CHARACTER FUNCTIONS
GraphicalEntity &GraphicalManager::characterInspect(int64_t id)
{
	if (m_entities.find(id) == m_entities.end())
		throw std::runtime_error("cannot find requested entity.");

	auto entity = m_entities[id].get();
	if (entity->type != EntityType::CHARACTER)
		throw std::runtime_error("requested entity isn't a character.");
	return (*entity);
}
void GraphicalManager::onCharacterIdle(int64_t id)
{
	auto character = characterInspect(id);

	//run idle animation

	if (character.status == GraphicalEntityStatus::IDLE)
		return;
}
void GraphicalManager::onCharacterMove(int64_t id)
{
	auto character = characterInspect(id);

	if (character.status == GraphicalEntityStatus::MOVING)
		return;

	//run moving animation

	character.status = GraphicalEntityStatus::MOVING;
}
void GraphicalManager::onCharacterDied(int64_t id)
{
	auto character = characterInspect(id);

	if (character.status == GraphicalEntityStatus::DYING)
		return;

	//run dying animation

	character.status = GraphicalEntityStatus::DYING;
}

