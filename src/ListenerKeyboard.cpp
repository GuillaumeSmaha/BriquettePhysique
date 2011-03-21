#include "ListenerKeyboard.h"

template<> ListenerKeyboard * ClassRootSingleton<ListenerKeyboard>::_instance = NULL;

void ListenerKeyboard::createSingleton()
{
	if(ListenerInputManager::getSingletonPtr()->getInputManager() != NULL)
	{
		new ListenerKeyboard();
	}
	else
	{
		std::cerr << "@ListenerKeyboard::createSingleton() : InputManager undefined" << std::endl;
	}
}

ListenerKeyboard::ListenerKeyboard() : ClassRootSingleton<ListenerKeyboard>()
{
    OIS::InputManager * inputManager = ListenerInputManager::getSingletonPtr()->getInputManager();
	this->keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	this->keyboard->setEventCallback(this);
}

ListenerKeyboard::~ListenerKeyboard()
{
	ListenerInputManager::getSingletonPtr()->getInputManager()->destroyInputObject(this->keyboard);
}

void ListenerKeyboard::capture()
{
    this->capture(NULL);
}

void ListenerKeyboard::capture(void *)
{
    this->keyboard->capture();
}

bool ListenerKeyboard::keyPressed(const OIS::KeyEvent &evt)
{
	this->signalKeyPressed.dispatch(evt);
	return true;
}


bool ListenerKeyboard::keyReleased(const OIS::KeyEvent &evt)
{
	this->signalKeyReleased.dispatch(evt);
	return true;
}
