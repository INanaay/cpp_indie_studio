//
// Created by lucas on 03/06/2018.
//

#ifndef INDIESTUDIO_DEMOSYSTEM_HPP
#define INDIESTUDIO_DEMOSYSTEM_HPP

#include <iostream>
#include "ISystem.hpp"

class World;

class DemoSystem : public ISystem {
public:
    DemoSystem(uint32_t x) : _x(x) {};
    void execute(World *ref) override {std::cout << "DemoSystem printing --> " << _x << std::endl;};
private:
    uint32_t _x;
};



#endif //INDIESTUDIO_DEMOSYSTEM_HPP
