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

class GraphicalManager
{
public:
	//CTOR DTOR
	GraphicalManager(const std::vector<GraphicalEntity> &entities); // will be use to initialize the MeshSceneNodes
	~GraphicalManager() = default;

	//FUNCTIONS
	void onCharacterIdle(int64_t id);
	void onCharacterMove(int64_t id);
	void onCharacterDied(int64_t id);

private:
	//FIELDS
	std::unordered_map<int64_t, std::unique_ptr<GraphicalEntity> > m_entities;

	//FUNCTIONS
	GraphicalEntity &characterInspect(int64_t id);

};

#endif //CPP_INDIE_STUDIO_RENDERER_HPP
