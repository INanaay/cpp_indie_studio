/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef CPP_INDIE_STUDIO_GAMEMANAGER_HPP
#define CPP_INDIE_STUDIO_GAMEMANAGER_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <entities/GameEntity.hpp>

class Core;

class GameManager
{
public:
	GameManager
	(Core &core, const std::vector<GameEntity> &entities);
private:
	Core *m_core;
	std::unordered_map<int, std::unique_ptr<GameEntity>> m_entities;
};


#endif //CPP_INDIE_STUDIO_GAMEMANAGER_HPP
