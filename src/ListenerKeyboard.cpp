#include "ListenerKeyboard.h"



ListenerKeyboard * ListenerKeyboard::_instance = NULL;

void ListenerKeyboard::createSingleton()
{
	if (_instance == NULL)
	{
		if(ListenerInputManager::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerKeyboard();
		}
		else
		{
			std::cerr << "@ListenerKeyboard::createSingleton() : InputManager undefined" << std::endl;
		}
	}
}

ListenerKeyboard * ListenerKeyboard::getSingletonPtr()
{
	if (_instance == NULL)
	{
		if(ListenerInputManager::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerKeyboard();
		}
		else
		{
			std::cerr << "@ListenerKeyboard::getSingletonPtr() : InputManager undefined" << std::endl;
		}
	}
	return _instance;
}

ListenerKeyboard & ListenerKeyboard::getSingleton()
{
	if (_instance == NULL)
	{
		if(ListenerInputManager::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerKeyboard();
		}
		else
		{
			std::cerr << "@ListenerKeyboard::getSingleton() : InputManager undefined" << std::endl;
		}
	}
	return *_instance;
}

void ListenerKeyboard::destroySingleton()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}


ListenerKeyboard::ListenerKeyboard()
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
