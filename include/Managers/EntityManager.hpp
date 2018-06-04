//
// Created by lucas on 04/06/2018.
//

#ifndef INDIESTUDIO_ENTITYMANAGER_HPP
#define INDIESTUDIO_ENTITYMANAGER_HPP

#include <vector>
#include <functional>

class Entity;

using Entities = std::vector<uint32_t>;

class EntityManager {
public:
    void addEntity(Entity &);
    const Entities &getEntities() const {return _added;};
    uint32_t getNextInstance();
    void foreachEntity(std::function<void(uint32_t)> fun) const;
private:
    Entities _added;
    uint32_t _entityCount = 0;
};

#endif //INDIESTUDIO_ENTITYMANAGER_HPP
