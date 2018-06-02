//
// Created by lucas on 31/05/2018.
//

#include <stdexcept>
#include <GraphicalEngine.hpp>

GraphicalEngine::GraphicalEngine(uint32_t x, uint32_t y)
{
    _device = irr::createDevice(irr::video::EDT_SOFTWARE,
            irr::core::dimension2d<irr::u32>(x, y), 16, false, false, false, 0);
    //_device->maximizeWindow();
    if (!_device)
        throw std::runtime_error("Cannot initialize device");
    _driver = _device->getVideoDriver();
    _scene = _device->getSceneManager();
    _gui = _device->getGUIEnvironment();
}