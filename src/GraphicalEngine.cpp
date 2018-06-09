//
// Created by lucas on 31/05/2018.
//

#define _IRR_COMPILE_WITH_OPENGL_

#include <stdexcept>
#include <GraphicalEngine.hpp>

GraphicalEngine::GraphicalEngine(uint32_t x, uint32_t y)
{
    _device = irr::createDevice(irr::video::EDT_SOFTWARE,
            irr::core::dimension2d<irr::u32>(x, y), 32, false, true, true, 0);
    //_device->maximizeWindow();
    if (!_device)
        throw std::runtime_error("Cannot initialize device");
    _driver = _device->getVideoDriver();
    _scene = _device->getSceneManager();
    _gui = _device->getGUIEnvironment();
	_metaSelector =  _scene->createMetaTriangleSelector();
}
