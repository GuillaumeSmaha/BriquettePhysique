#include "ListenerKeyboard.h"



ListenerKeyboard * ListenerKeyboard::_instance = NULL;

void ListenerKeyboard::createSingleton()
{
	if (_instance == NULL)
	{
		if(Application::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerKeyboard();
		}
	}
}

ListenerKeyboard * ListenerKeyboard::getSingletonPtr()
{
	if (_instance == NULL)
	{
		if(Application::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerKeyboard();
		}
	}
	return _instance;
}

ListenerKeyboard & ListenerKeyboard::getSingleton()
{
	if (_instance == NULL)
	{
		if(Application::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerKeyboard();
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
    OIS::InputManager * inputManager = Application::getSingletonPtr()->getInputManager();
	this->keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	this->keyboard->setEventCallback(this);
}

ListenerKeyboard::~ListenerKeyboard()
{
	Application::getSingletonPtr()->getInputManager()->destroyInputObject(this->keyboard);
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
