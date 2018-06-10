//
// Created by NANAA on 10/06/18.
//

#ifndef INDIESTUDIO_PICKUP_HPP
#define INDIESTUDIO_PICKUP_HPP

#include <Interfaces/IComponent.hpp>
#include <GraphicalEngine.hpp>

enum PickupType
{
	SPEEDPICKUP,
	RADIUSPICKUP,
	BOMBPICKUP
};

namespace Components {
	class Pickup : public IComponent
	{
	public:
		Pickup(PickupType type) : pickupType(type) {};
		~Pickup() override = default;
		void summarize() const override {};
		typeComponent getType() const override { return PICKUP; };
		PickupType pickupType;
	};
}

#endif //INDIESTUDIO_PICKUP_HPP
