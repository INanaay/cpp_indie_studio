/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef CPP_INDIE_STUDIO_RENDERER_HPP
#define CPP_INDIE_STUDIO_RENDERER_HPP

#include <unordered_map>
#include <IAnimatedMeshSceneNode.h>
#include <memory>
#include "GraphicalEntity.hpp"

class Renderer
{
public:
	//CTOR DTOR
	Renderer(const std::vector<GraphicalEntity> &entities); // will be use to initialize the MeshSceneNodes
	~Renderer() = default;

	//FUNCTIONS
	void onCharacterIdle(int64_t id);
	void onCharacterMove(int64_t id);
	void onCharacterDied(int64_t id);

private:
	//FIELDS
	std::unordered_map<int64_t, std::unique_ptr<GraphicalEntity>> m_entities;

	//FUNCTIONS
	GraphicalEntity &characterInspect(int64_t id);

};

#endif //CPP_INDIE_STUDIO_RENDERER_HPP
