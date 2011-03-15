#include "ListenerFrame.h"


ListenerFrame * ListenerFrame::_instance = NULL;

void ListenerFrame::createSingleton()
{
	if (_instance == NULL)
	{
		_instance = new ListenerFrame();
	}
}

ListenerFrame * ListenerFrame::getSingletonPtr()
{
	if (_instance == NULL)
	{
		_instance = new ListenerFrame();
	}
	return _instance;
}

ListenerFrame & ListenerFrame::getSingleton()
{
	if (_instance == NULL)
	{
		_instance = new ListenerFrame();
	}
	return *_instance;
}

void ListenerFrame::destroySingleton()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}


ListenerFrame::ListenerFrame(): closed(false)
{
   	Application::getSingletonPtr()->getRoot()->addFrameListener(this);
}

ListenerFrame::~ListenerFrame()
{
}

bool ListenerFrame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(this->closed)
    {
        return false;
    }

    this->signalFrameRendering.dispatch();
	return true;
}

bool ListenerFrame::frameStarted(const Ogre::FrameEvent &evt)
{
	this->signalFrameStarted.dispatch(evt);
    return true;
}

bool ListenerFrame::frameEnded(const Ogre::FrameEvent &evt)
{
	this->signalFrameEnded.dispatch(evt);
	return true;
}


void ListenerFrame::shutdown()
{
    this->shutdown(NULL);

}
void ListenerFrame::shutdown(void*)
{
    this->closed = true;

}
