/*
** EPITECH PROJECT, 2018
** getfilecontent
** File description:
** getfilecontent
*/

#include <iostream>
#include <random>
#include "Map.hpp"

static unsigned char myRand(std::size_t from, std::size_t to)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> toRet(from, to);
	return toRet(rng);
}

static std::vector<unsigned char> unusedLine(unsigned int size)
{
	std::vector<unsigned char> test;

	for (unsigned int i = 0; i < size; i++)
		test.push_back('0');
	return test;
}

void Map::fillMapRandomly() noexcept
{
        int nbWall;

	/* destroy map if already initialized */
	_map.clear();

	/* push vector of char in the "main" vector in order to create a "2d" table */
        for (int i = 0; i < Y_MAP; i++)
                _map.push_back(unusedLine(X_MAP));

	/* add walls randomly */
        for (unsigned int y = 1; y < Y_MAP; y++) {
                nbWall = myRand(0, 5) % 9;
                for (int x = 0; x < nbWall; x++) {
                        int getRand = myRand(0, 5) % X_MAP;
                        if (_map[y][getRand] == '1')
                                x--;
                        else
                                _map[y][myRand(0, X_MAP)] = '1';
                }
        }
}

void Map::printMap() noexcept
{
	for (auto y : _map) {
		for (auto x : y) {
			std::cout << x;
		}
		std::cout << std::endl;
	}
}

void Map::physicalMapToGraphicalEntity() noexcept
{
	for (unsigned int y = 0 ; y < Y_MAP ; y++) {
		for (unsigned int x = 0 ; x < X_MAP ; x++) {
			EntityPosition positionToPush;
			positionToPush.y = y;
			positionToPush.x = x;
			positionToPush.z = 0;

		}
	}
	std::cout << "game vector length: " << _gameMap.size() <<  std::endl;
}

Map::Map(int noiselevel)
{
	(void)noiselevel;
	fillMapRandomly();
	printMap();
	physicalMapToGraphicalEntity();
}
