//
// Created by lucas on 02/06/2018.
//

#ifndef INDIESTUDIO_ISYSTEMS_HPP
#define INDIESTUDIO_ISYSTEMS_HPP

class World;

/*!
 * \brief This interface define the comportement of a system
 */

class ISystem {
public:
    virtual void execute(World *) = 0;
    virtual ~ISystem() = default;
private:
};

#endif //INDIESTUDIO_ISYSTEMS_HPP
