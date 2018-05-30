/*
** EPITECH PROJECT, 2018
** getfilecontent
** File description:
** getfilecontent
*/

#ifndef ___MAP_HPP___
#define ___MAP_HPP___

#include "GraphicalEntity.hpp"
#include "BaseEntity.hpp"
#include "GameEntity.hpp"
#include <vector>

#define Y_MAP 21
#define X_MAP 21

class Map {
public:
	Map(int);
	void fillMapRandomly() noexcept;
	void physicalMapToGraphicalEntity() noexcept;
	void AddBlueNoise();
	void printMap() noexcept;
	~Map() = default;
private:
	std::vector<std::vector<unsigned char>> _map;
	std::vector<GameEntity> _gameMap;
};

#endif /* ___MAP_HPP___ */