//
// Created by NANAA on 31/05/18.
//

#include <irrlicht.h>

#ifndef IRRLITCHTEST_MENUEVENTHANDLER_HPP
#define IRRLITCHTEST_MENUEVENTHANDLER_HPP

extern bool is_running;

struct SAppContext
{
	irr::IrrlichtDevice *device;
	bool isRunning;
	int nbPlayers;
};

enum Buttonss
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_ONE_PLAYER = 102,
	GUI_ID_TWO_PLAYERS = 103
};

class MenuEventHandler : public irr::IEventReceiver
{
public:
	explicit MenuEventHandler(SAppContext &context);
	bool OnEvent(const irr::SEvent &event) override;

private:
	SAppContext &m_context;
public:
	void setM_context(SAppContext &m_context);
};


#endif //IRRLITCHTEST_MENUEVENTHANDLER_HPP
