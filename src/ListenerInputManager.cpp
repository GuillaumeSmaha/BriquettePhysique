#include "ListenerInputManager.h"


ListenerInputManager * ListenerInputManager::_instance = NULL;

void ListenerInputManager::createSingleton()
{
	if (_instance == NULL)
	{
		if(ListenerWindow::getSingletonPtr()->getRenderWindow() != NULL)
		{
			_instance = new ListenerInputManager();
		}
		else
		{
			std::cerr << "@ListenerInputManager::createSingleton() : InputManager undefined" << std::endl;
		}
	}
}

ListenerInputManager * ListenerInputManager::getSingletonPtr()
{
	if (_instance == NULL)
	{
		if(ListenerWindow::getSingletonPtr()->getRenderWindow() != NULL)
		{
			_instance = new ListenerInputManager();
		}
		else
		{
			std::cerr << "@ListenerInputManager::getSingletonPtr() : InputManager undefined" << std::endl;
		}
	}
	return _instance;
}

ListenerInputManager & ListenerInputManager::getSingleton()
{
	if (_instance == NULL)
	{
		if(ListenerWindow::getSingletonPtr()->getRenderWindow() != NULL)
		{
			_instance = new ListenerInputManager();
		}
		else
		{
			std::cerr << "@ListenerInputManager::getSingleton() : InputManager undefined" << std::endl;
		}
	}
	return *_instance;
}

void ListenerInputManager::destroySingleton()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}


ListenerInputManager::ListenerInputManager()
{
	// Init the input system manager
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	ListenerWindow::getSingletonPtr()->getRenderWindow()->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	
	this->inputManager = OIS::InputManager::createInputSystem(pl);
}

ListenerInputManager::~ListenerInputManager()
{
}
