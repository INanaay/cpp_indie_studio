//
// Created by NANAA on 07/06/18.
//

#ifndef INDIESTUDIO_WALLCOLLISION_HPP
#define INDIESTUDIO_WALLCOLLISION_HPP

#include <Interfaces/IComponent.hpp>
#include <ITriangleSelector.h>
#include <iostream>

namespace Components {
	class WallCollision : public IComponent {
	public:
		WallCollision() : selector(nullptr), isLoaded(false) {};
		~WallCollision() override = default;
		typeComponent getType() const override { return WALLCOLLISION;};
		void summarize() const override
		{std::cout << "This wall has collisions." << std::endl;}
		irr::scene::ITriangleSelector* selector;
		bool isLoaded;
	};
}

#endif //INDIESTUDIO_WALLCOLLISION_HPP
