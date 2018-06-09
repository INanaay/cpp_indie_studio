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
        void removeComponent(uint32_t, typeComponent);
        void removeComponents();
        ComponentsList &getComponents(uint32_t);
        std::vector<uint32_t> getEntityByComponents(std::vector<typeComponent>) const;
        void infoComponent(uint32_t);

        template <class T>
        T *getComponent(uint32_t id, typeComponent search) {
            for (auto &e : _entities[id]) {
                if (e->getType() == search) {
                    return (static_cast<T *>(e.get()));
                }
            }
            return nullptr;
        }

    private:
        EntitiesComponents _entities;
};

#endif //INDIESTUDIO_COMPONENTMANAGER_HPP
