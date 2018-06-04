//
// Created by lucas on 02/06/2018.
//

#ifndef INDIESTUDIO_COMPONENTMANAGER_HPP
#define INDIESTUDIO_COMPONENTMANAGER_HPP

#include <unordered_map>
#include <memory>
#include <vector>
#include "IComponent.hpp"

using ComponentsList = std::vector<std::unique_ptr<IComponent>>;
using EntitiesComponents = std::unordered_map<uint32_t, ComponentsList>;

/*!
 * \brief This class is an encapsulation for adding / deleting components to an Entity
 */

class ComponentManager {
    public:
        void addComponent(IComponent *, uint32_t);
        ComponentsList &getComponent(uint32_t);
        std::vector<uint32_t> getEntityByComponents(std::vector<typeComponent>) const;
        void infoComponent(uint32_t);
    private:
        EntitiesComponents _entities;
};

#endif //INDIESTUDIO_COMPONENTMANAGER_HPP
