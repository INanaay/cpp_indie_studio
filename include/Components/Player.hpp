//
// Created by NANAA on 13/06/18.
//

#ifndef INDIESTUDIO_PLAYER_HPP
#define INDIESTUDIO_PLAYER_HPP

#include <Interfaces/IComponent.hpp>

namespace Components {
	class Player : public IComponent
	{
	public:
		Player() {};
		~Player() override = default;
		void summarize() const override {};
		typeComponent getType() const override { return PLAYER; };
	};
}


#endif //INDIESTUDIO_PLAYER_HPP
