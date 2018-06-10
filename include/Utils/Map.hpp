/*
** EPITECH PROJECT, 2018
** getfilecontent
** File description:
** getfilecontent
*/

#ifndef ___MAP_HPP___
#define ___MAP_HPP___

#include <vector>
#include "World.hpp"

#define WALL_LENGTH 15
#define PLAYABLE (WALL_LENGTH - 1)

using typeMap = std::vector<std::vector<unsigned char>>;

class Map {
public:
	explicit Map();
	void fillMapRandomly() noexcept;
	void addUnbreakableWalls() noexcept;
	void physicalMapToGraphicalEntity() noexcept;
	void cleanCornersAddPlayers() noexcept;
	void addOutsideWalls() noexcept;
	void addFlowers(World &) noexcept;

	typeMap const &getMap() const noexcept { return _map; }
	void load3DMap(World &, int);
	void printMap() noexcept;
	~Map() = default;
private:
	typeMap _map;
};

#endif /* ___MAP_HPP___ */
