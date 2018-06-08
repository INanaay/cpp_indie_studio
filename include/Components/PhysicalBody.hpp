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
	class PhysicalBody : public IComponent {
	public:
		enum Direction {
			UP = 180,
			DOWN = 0,
			LEFT = 90,
			RIGHT = 270
		};
	public:
		PhysicalBody(float xs, float ys, float zs) : x(xs), y(ys), z(zs), direction(DOWN) {};
		~PhysicalBody() override = default;
		void summarize() const override
			{ std::cout << "PhysicalBody | X : " << x << " | Y : " << y << " | Z : " << z << " | Direction : " << direction << std::endl; };
		typeComponent getType() const override { return PHYSICALBODY; };
		bool dropBomb() {
			if (!has_dropped) {
				has_dropped = true;
				return (true);
			}
			return (false);
		}
	public:
		float x;
		float y;
		float z;
		Direction direction;
		bool has_dropped = false;
	};
}

//w = 180 s = 0 a = 90 d = 270

#endif //INDIESTUDIO_PHYSICALBODY_HPP