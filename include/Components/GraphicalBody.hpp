//
// Created by lucas on 04/06/2018.
//

#ifndef INDIESTUDIO_GRAPHICALBODY_HPP
#define INDIESTUDIO_GRAPHICALBODY_HPP

#include <string>
#include <iostream>
#include <irrlicht.h>
#include "IComponent.hpp"

namespace Components {
    class GraphicalBody : public IComponent {
    public:
        GraphicalBody(std::string&& model, std::string&& texture)
                : pathToModel(model), pathToTexture(texture), node(nullptr), isLoaded(false) {};
        ~GraphicalBody() override = default;
        void summarize() const override {
            std::cout << "GraphicalBody | Model : " << pathToModel
                      << " | Texture : " << pathToTexture << std::endl;
        };
        typeComponent getType() const override { return GRAPHICALBODY; };

    public:
	    std::string pathToModel;
	    std::string pathToTexture;
	    irr::scene::IAnimatedMeshSceneNode *node;
	    irr::scene::IAnimatedMesh *mesh;
	    bool isLoaded;
    };
}

#endif //INDIESTUDIO_GRAPHICALBODY_HPP
