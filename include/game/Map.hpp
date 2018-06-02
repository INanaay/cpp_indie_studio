/*
** EPITECH PROJECT, 2018
** getfilecontent
** File description:
** getfilecontent
*/

#ifndef ___MAP_HPP___
#define ___MAP_HPP___

#include <vector>
#include "BaseEntity.hpp"

#define Y_MAP 21
#define X_MAP 21

class Map {
public:
	Map(int);
	void fillMapRandomly() noexcept;
	void physicalMapToGraphicalEntity() noexcept;
	void AddBlueNoise() {};
	void printMap() noexcept;
	~Map() = default;
private:
	std::vector<std::vector<unsigned char>> _map;
	std::vector<BaseEntity> _gameMap;
};

#endif /* ___MAP_HPP___ */
