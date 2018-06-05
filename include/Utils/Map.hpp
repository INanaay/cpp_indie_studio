/*
** EPITECH PROJECT, 2018
** getfilecontent
** File description:
** getfilecontent
*/

#ifndef ___MAP_HPP___
#define ___MAP_HPP___

#include <vector>

#define WALL_LENGTH 21
#define PLAYABLE 20

using typeMap = std::vector<std::vector<unsigned char>>;

class Map {
public:
	Map(int);
	void fillMapRandomly() noexcept;
	void addUnbreakableWalls() noexcept;
	void physicalMapToGraphicalEntity() noexcept;
	void cleanCornersAddPlayers() noexcept;
	void addOutsideWalls() noexcept;

	typeMap const &getMap() const noexcept { return _map; }

	void printMap() noexcept;
	~Map() = default;
private:
	typeMap _map;
};

#endif /* ___MAP_HPP___ */
