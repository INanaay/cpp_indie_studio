//
// Created by lucas on 02/06/2018.
//

#ifndef INDIESTUDIO_COMPONENTMANAGER_HPP
#define INDIESTUDIO_COMPONENTMANAGER_HPP

#include <unordered_map>
#include <memory>
#include "ComponentManager.hpp"
#include "IComponent.hpp"

using EntitiesComponents = std::unordered_map<uint32_t, std::vector<std::unique_ptr<IComponent>>>;

/*!
 * \brief This class is an encapsulation for adding / deleting components to an Entity
 */

class ComponentManager {
    public:
        void addComponent(IComponent *, uint32_t);
        void infoComponent(uint32_t);
    private:
        EntitiesComponents _entities;
};

#endif //INDIESTUDIO_COMPONENTMANAGER_HPP
