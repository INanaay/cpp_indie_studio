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

	for (unsigned int i = 0; i <= size; i++)
		test.push_back('0');
	return test;
}

void Map::fillMapRandomly() noexcept
{
        int nbWall;

	/* destroy map if already initialized */
	_map.clear();

	/* push vector of char in the "main" vector in order to create a "2d" table */
        for (int i = 0; i <= WALL_LENGTH; i++)
                _map.push_back(unusedLine(WALL_LENGTH));

	/* add walls randomly */
        for (unsigned int y = 1; y <= WALL_LENGTH; y++) {
                nbWall = myRand(PLAYABLE / 2, PLAYABLE);
                for (int x = 0; x < nbWall; x++) {
                        int getRand = myRand(0, PLAYABLE);
                        if (_map[y][getRand] == '1')
                                x--;
                        else
                                _map[y][myRand(0, PLAYABLE)] = '1';
                }
        }
}

static int checkSurroundings(typeMap &map, int py, int px) noexcept
{
	for (int y = -1 ; y < 2 ; y++) {
		for (int x = -1 ; x < 2 ; x++) {
			if (y == 0 && x == 0)
				continue ;
			if (py + y >= 0 && px + x >= 0 &&
				py + y <= PLAYABLE && px + x <= PLAYABLE) {
				if (map[py + y][px + x] == '2')
					return 1;
			}
		}
	}
	return 0;
}

/* blue noise generation */
void Map::addUnbreakableWalls() noexcept
{
	int nbWall;

	for (unsigned int y = 1; y <= WALL_LENGTH; y++) {
		nbWall = myRand(0, PLAYABLE / 4);
		for (int x = 0; x < nbWall; x++) {
			int getRand = myRand(0, PLAYABLE);
			if (checkSurroundings(_map, y, getRand) == 0)
				_map[y][getRand] = '2';
		}
	}
}

void Map::physicalMapToGraphicalEntity() noexcept
{
	for (unsigned int y = 0 ; y <= WALL_LENGTH ; y++) {
		for (unsigned int x = 0 ; x <= WALL_LENGTH ; x++) {
			/* to do once the node is updated */
		}
	}
}

void Map::addOutsideWalls() noexcept
{
	int val;
	int stockVal;

	for (val = 0; val < WALL_LENGTH ; val++) {
		_map[val][0] = '2';
		_map[0][val] = '2';
	}
	stockVal = val;
	for (; val >= 0; val--) {
		_map[stockVal][val] = '2';
		_map[val][stockVal] = '2';
	}
}

void Map::cleanCornersAddPlayers() noexcept
{
	_map[1][1 + 1] = '0';
	_map[1 + 1][1] = '0';
	_map[1][PLAYABLE - 1] = '0';
	_map[1][PLAYABLE] = '0';
	_map[PLAYABLE - 1][1] = '0';
	_map[PLAYABLE][1] = '0';
	_map[PLAYABLE][PLAYABLE - 1] = '0';
	_map[PLAYABLE - 1][PLAYABLE] = '0';

	_map[1][1] = 'a';
	_map[PLAYABLE][PLAYABLE] = 'c';
	_map[1][PLAYABLE] = 'b';
	_map[PLAYABLE][1] = 'd';
}

Map::Map(int noiselevel)
{
	(void)noiselevel;
	fillMapRandomly();
	addUnbreakableWalls();
	addOutsideWalls();
	cleanCornersAddPlayers();
	printMap();
	//physicalMapToGraphicalEntity();
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