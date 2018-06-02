//
// Created by lucas on 30/05/2018.
//

#include <iostream>
#include <Core.hpp>
#include <Menu.hpp>
#include <MenuEventHandler.hpp>
#include "GraphicalEngine.hpp"
#include "Menu.hpp"

// Pipeline
// 1. Generate map
// 2. Load what is needed
// 3. Execute logic

int main()
{
    try {
        Core core;

        core.menu();

        std::cout << "Started the game" << std::endl;

        core.play();


    } catch (...) {

    }
}
