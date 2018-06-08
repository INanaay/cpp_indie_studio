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
                : pathToModel(model), pathToTexture(texture), player_id(player_id), radius(radius), node(nullptr), isLoaded(false), timer(std::chrono::system_clock::now()) {};
        ~Bomb() override = default;
        void summarize() const override {
            std::cout << "Bomb | Model : " << pathToModel
                      << " | Texture : " << pathToTexture << std::endl;
        };
        typeComponent getType() const override { return BOMB; };
        bool explode(std::chrono::time_point<std::chrono::system_clock> c_time) {
            return (std::chrono::duration_cast<std::chrono::milliseconds>(c_time - timer) >  std::chrono::milliseconds(2000));
        };
        void setPos(float xx, float yy, float zz) {
            x = xx;
            y = yy;
            z = zz;
        }
    public:
        std::string pathToModel;
        std::string pathToTexture;
        irr::scene::IAnimatedMeshSceneNode *node;
        bool isLoaded;
        float radius;
        uint32_t player_id;
        float x;
        float y;
        float z;
        std::chrono::time_point<std::chrono::system_clock> timer;
    };
}

#endif