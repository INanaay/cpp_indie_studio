//
// Created by lucas on 02/06/2018.
//

#ifndef INDIESTUDIO_IENTITYCOMPONENT_H
#define INDIESTUDIO_IENTITYCOMPONENT_H

enum typeComponent {
	AI,
	PHYSICALBODY,
	GRAPHICALBODY,
	POSITION,
	VELOCITY,
	WALLCOLLISION,
	PLAYERCOLLISION,
    CONTROLLABLE,
	BOMBMANAGER,
	TIMER
};

/*!
 * \brief This interface define the comportement of a component
 */

class IComponent {
public:
    virtual typeComponent getType() const = 0;
    virtual void summarize() const = 0;
    virtual ~IComponent() = default;
};

#endif //INDIESTUDIO_IENTITYCOMPONENT_H
