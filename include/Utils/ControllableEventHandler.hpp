//
// Created by lucas on 05/06/2018.
//

#ifndef INDIESTUDIO_CONTROLLABLEEVENTHANDLER_HPP
#define INDIESTUDIO_CONTROLLABLEEVENTHANDLER_HPP

#include <irrlicht.h>

class ControllableEventHandler : public irr::IEventReceiver
{
public:
    virtual bool OnEvent(const irr::SEvent& event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    bool *getKeyDownArray()
    {
        return &KeyIsDown[0];
    }



    ControllableEventHandler()
    {
        for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif //INDIESTUDIO_CONTROLLABLEEVENTHANDLER_HPP
