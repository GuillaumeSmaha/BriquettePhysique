#include "ListenerFrame.h"

template<> ListenerFrame * ClassRootSingleton<ListenerFrame>::_instance = NULL;

ListenerFrame::ListenerFrame(Ogre::Root * root) : ClassRootSingleton<ListenerFrame>(), closed(false)
{
   	//Application::getSingletonPtr()->getRoot()->addFrameListener(this);
   	root->addFrameListener(this);
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
