//
// Created by NANAA on 07/06/18.
//

#include <Interfaces/IComponent.hpp>
#include <ISceneNodeAnimatorCollisionResponse.h>
#include <iostream>

#ifndef INDIESTUDIO_PLAYERCOLLISION_HPP
#define INDIESTUDIO_PLAYERCOLLISION_HPP

#endif //INDIESTUDIO_PLAYERCOLLISION_HPP

namespace Components {
	class PlayerCollision : public IComponent {
	public:
		PlayerCollision() : anim(nullptr), isLoaded(false) {};
		~PlayerCollision() override = default;
		typeComponent getType() const override { return PLAYERCOLLISION;};
		void summarize() const override
		{ std::cout << "This player has collisions" << std::endl;}
		irr::scene::ISceneNodeAnimatorCollisionResponse  *anim;
		bool isLoaded;
	};
}