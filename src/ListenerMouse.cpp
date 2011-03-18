#include "ListenerMouse.h"


ListenerMouse * ListenerMouse::_instance = NULL;

void ListenerMouse::createSingleton()
{
	if (_instance == NULL)
	{
		if(ListenerInputManager::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerMouse();
		}
		else
		{
			std::cerr << "@ListenerMouse::createSingleton() : InputManager undefined" << std::endl;
		}
	}
}

ListenerMouse * ListenerMouse::getSingletonPtr()
{
	if (_instance == NULL)
	{
		if(ListenerInputManager::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerMouse();
		}
		else
		{
			std::cerr << "@ListenerMouse::getSingletonPtr() : InputManager undefined" << std::endl;
		}
	}
	return _instance;
}

ListenerMouse & ListenerMouse::getSingleton()
{
	if (_instance == NULL)
	{
		if(ListenerInputManager::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerMouse();
		}
		else
		{
			std::cerr << "@ListenerMouse::getSingleton() : InputManager undefined" << std::endl;
		}
	}
	return *_instance;
}

void ListenerMouse::destroySingleton()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}


ListenerMouse::ListenerMouse()
{
	OIS::InputManager * inputManager = ListenerInputManager::getSingletonPtr()->getInputManager();
	this->mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
	this->mouse->setEventCallback(this);
}

ListenerMouse::~ListenerMouse()
{
	ListenerInputManager::getSingletonPtr()->getInputManager()->destroyInputObject(this->mouse);
}

void ListenerMouse::capture()
{
    this->capture(NULL);
}

void ListenerMouse::capture(void *)
{
    this->mouse->capture();
}

bool ListenerMouse::mouseMoved(const OIS::MouseEvent &evt)
{
	this->signalMouseMoved.dispatch(Ogre::Vector3(evt.state.X.rel, evt.state.Y.rel, evt.state.Y.rel));

	return true;
}

bool ListenerMouse::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    this->signalMousePressed.dispatch(id);
	return true;
}

bool ListenerMouse::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{

    this->signalMouseReleased.dispatch(id);
	return true;
}
