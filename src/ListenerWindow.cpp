#include "ListenerWindow.h"


ListenerWindow * ListenerWindow::_instance = NULL;


void ListenerWindow::createSingleton(Ogre::String windowName)
{
	if (_instance == NULL)
	{
		_instance = new ListenerWindow(windowName);
	}
}

ListenerWindow * ListenerWindow::getSingletonPtr()
{
	if (_instance == NULL)
	{
		_instance = new ListenerWindow();
	}
	return _instance;
}

ListenerWindow & ListenerWindow::getSingleton()
{
	if (_instance == NULL)
	{
		_instance = new ListenerWindow();
	}
	return *_instance;
}


ListenerWindow::ListenerWindow()
{
	if (_instance == NULL)
	{
		this->renderWindow = Application::getSingleton()->getRoot()->initialise(true, "Generic Window");
		Ogre::WindowEventUtilities::addWindowEventListener(this->renderWindow, this);
		this->windowResized(this->renderWindow);
		_instance = this;
	}
}

ListenerWindow::ListenerWindow(Ogre::String windowName)
{
	if (_instance == NULL)
	{
		this->renderWindow = Application::getSingleton()->getRoot()->initialise(true, windowName);
		Ogre::WindowEventUtilities::addWindowEventListener(this->renderWindow, this);
		this->windowResized(this->renderWindow);
		_instance = this;
	}
}

ListenerWindow::~ListenerWindow()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(this->renderWindow, this);
	this->windowClosed(this->renderWindow);
}

void ListenerWindow::windowResized(Ogre::RenderWindow * rw)
{
	if(ListenerMouse::getSingletonPtr() != NULL)
	{
		unsigned int width, height, depth;
		int left, top;

		rw->getMetrics(width, height, depth, left, top);
		const OIS::MouseState &ms = ListenerMouse::getSingletonPtr()->getMouse()->getMouseState();
		ms.width = width;
		ms.height = height;
	}
}

void ListenerWindow::windowClosed(Ogre::RenderWindow * rw)
{
	if(rw == this->renderWindow)
	{
		this->signalWindowClosed.dispatch();
	}
}
