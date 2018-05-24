#include <irrlicht.h>
#include <iostream>


class MyEventReceiver : public irr::IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const irr::SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	MyEventReceiver()
	{
		for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	bool isAnyKeyPressed()
	{

		for (auto i : KeyIsDown) {
			if (i)
				return true;
		}
		return false;

	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

enum characteranimation
{
	Iddle,
	moving,
	dab
};

void animate(irr::scene::IAnimatedMeshSceneNode *node, characteranimation &anim)
{
	if (anim == Iddle) {
		anim = moving;
		node->setFrameLoop(1, 35);
			node->setCurrentFrame(1);
	}
	node->setAnimationSpeed(60);
}


int main()
{
	MyEventReceiver receiver;

	irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(640, 480), 16,
							false, false, false, &receiver) ;
	device->setWindowCaption(L"Slt");
	irr::video::IVideoDriver *driver = device->getVideoDriver();
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment *guienv = device->getGUIEnvironment();
	guienv->addStaticText(L"Yo cesst un test", irr::core::rect<irr::s32>(10, 10, 262, 22), true);
	irr::scene::IAnimatedMesh *mesh = smgr->getMesh("rere.b3d");


	if (!mesh)
	{
		device->drop();
		return 1;
	}
	irr::scene::IAnimatedMeshSceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);
	characteranimation anim = Iddle;
	if (node)
	{
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//node->setMaterialTexture(0, driver->getTexture("re.png") );
		//node->setPosition(irr::core::vector3df(0,0,30));

	}


	smgr->addCameraSceneNode(0, irr::core::vector3df(0, 10,-10), irr::core::vector3df(0,5,0));


	int lastFPS = -1;
	irr::u32 then = device->getTimer()->getTime();
	const irr::f32 MOVEMENT_SPEED = 15.f;


	while (device->run()) {


		int frame = (int) node->getFrameNr();
		std::cout << "Current framne = " << frame << std::endl;
		if (anim == Iddle)
			node->setFrameLoop(34, 34);
		if (anim == dab)
		{
			if ( frame == 50)
				anim = Iddle;
		}
		else if (receiver.isAnyKeyPressed() == 0 ) {
			anim = Iddle;
			//node->setFrameLoop(34, 34);

		}

		const irr::u32 now = device->getTimer()->getTime();
		const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f; // Time in seconds
		then = now;
		irr::core::vector3df nodePosition = node->getPosition();
		if(receiver.IsKeyDown(irr::KEY_KEY_W)) {
			node->setRotation(irr::core::vector3df(0, 180, 0));

			nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
			animate(node, anim);
		}
		else if(receiver.IsKeyDown(irr::KEY_KEY_S)) {
			node->setRotation(irr::core::vector3df(0, -0, 0));

			nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
			animate(node, anim);

		}
		if(receiver.IsKeyDown(irr::KEY_KEY_A)) {
			node->setRotation(irr::core::vector3df(0, 90, 0));
			nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
			animate(node, anim);

		}
		else if(receiver.IsKeyDown(irr::KEY_KEY_D)) {
			node->setRotation(irr::core::vector3df(0, -90, 0));
			nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
			animate(node, anim);
		}
		else if (receiver.IsKeyDown(irr::KEY_KEY_J))
		{

			anim = dab;
			node->setFrameLoop(34, 52);
			node->setCurrentFrame(34);
			node->setAnimationSpeed(10);

		}


		node->setPosition(nodePosition);

		driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			irr::core::stringw tmp(L"Movement Example - Irrlicht Engine [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
	}
	device->drop();
	return 0;
}
