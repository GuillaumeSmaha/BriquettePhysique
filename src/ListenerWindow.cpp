#include "ListenerWindow.h"

template<> ListenerWindow * ClassRootSingleton<ListenerWindow>::_instance = NULL;

void ListenerWindow::createSingleton()
{
	ListenerWindow::createSingleton("Generic Window");
}

void ListenerWindow::createSingleton(Ogre::String windowName)
{
	new ListenerWindow(windowName);
}

ListenerWindow::ListenerWindow(Ogre::String windowName) : ClassRootSingleton<ListenerWindow>()
{
	this->renderWindow = Application::getSingletonPtr()->getRoot()->initialise(true, windowName);
	Ogre::WindowEventUtilities::addWindowEventListener(this->renderWindow, this);
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
