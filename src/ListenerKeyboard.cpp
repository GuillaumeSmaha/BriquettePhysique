#include "ListenerKeyboard.h"



ListenerKeyboard * ListenerKeyboard::_instance = NULL;

void ListenerKeyboard::createSingleton(OIS::InputManager * inputManager)
{
	if (_instance == NULL)
	{
		_instance = new ListenerKeyboard(inputManager);
	}
}

ListenerKeyboard * ListenerKeyboard::getSingletonPtr()
{
	if (_instance == NULL)
	{
		return NULL;
	}
	return _instance;
}

ListenerKeyboard & ListenerKeyboard::getSingleton()
{
	if (_instance == NULL)
	{
		return NULL;
	}
	return *_instance;
}

ListenerKeyboard::ListenerKeyboard(OIS::InputManager * inputManager)
{
    this->inputManager = inputManager;
	this->keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	this->keyboard->setEventCallback(this);
}

ListenerKeyboard::~ListenerKeyboard()
{
	this->inputManager->destroyInputObject(this->keyboard);
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
