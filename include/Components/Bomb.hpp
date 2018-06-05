/*
** EPITECH PROJECT, 2018
** Project Name
** File description:
** bomb component
*/


#ifndef INDIESTUDIO_BOMB_HPP
#define INDIESTUDIO_BOMB_HPP

#include <string>
#include <iostream>
#include <irrlicht.h>
#include <chrono>
#include <ctime>
#include "IComponent.hpp"

namespace Components {
    class Bomb : public IComponent {
    public:
        Bomb(std::string&& model, std::string&& texture, uint32_t player_id, float radius)
                : pathToModel(model), pathToTexture(texture), player_id(player_id), radius(radius), node(nullptr), isLoaded(false), timer(std::clock()) {};
        ~Bomb() override = default;
        void summarize() const override {
            std::cout << "Bomb | Model : " << pathToModel
                      << " | Texture : " << pathToTexture << std::endl;
        };
        typeComponent getType() const override { return BOMB; };
        bool explode(std::clock_t c_time) {
            return (std::chrono::duration<double, std::milli>(c_time - timer).count() > 2000);
        };
    public:
        std::string pathToModel;
        std::string pathToTexture;
        irr::scene::IAnimatedMeshSceneNode *node;
        bool isLoaded;
        float radius;
        uint32_t player_id;
        std::clock_t timer;
    };
}

#endif