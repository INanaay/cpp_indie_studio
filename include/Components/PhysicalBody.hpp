/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/06 by cjdcoy
*/

#ifndef INDIESTUDIO_PHYSICALBODY_HPP
#define INDIESTUDIO_PHYSICALBODY_HPP

#include <iostream>
#include "IComponent.hpp"

namespace Components {
	class Position : public IComponent {
		enum Direction {
			UP = 180,
			DOWN = 0,
			LEFT = 90,
			RIGHT = 270
		};
	public:
		Position(unsigned int xs, unsigned int ys, unsigned int zs) : x(xs), y(ys), z(zs), direction(UP) {};
		~Position() override = default;
		void summarize() const override { std::cout << "Position | X : " << x << " | Y : " << y << " | Z : " << z
							    << "direction : " << direction << std::endl; };
		typeComponent getType() const override { return PHYSICALBODY; };
	public:
		unsigned int x;
		unsigned int y;
		unsigned int z;
		Direction direction;
	};
}

//w = 180 s = 0 a = 90 d = 270

#endif //INDIESTUDIO_PHYSICALBODY_HPP