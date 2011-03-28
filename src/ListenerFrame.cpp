#include "ListenerFrame.h"

template<> ListenerFrame * ClassRootSingleton<ListenerFrame>::_instance = NULL;


void ListenerFrame::createSingleton()
{
	if (_instance == NULL)
	{
		new ListenerFrame();
	}
}

void ListenerFrame::createSingleton(Ogre::Root * root)
{
	if (_instance == NULL)
	{
		new ListenerFrame(root);
	}
}

ListenerFrame::ListenerFrame() : closed(false)
{
	std::cerr << "Le constructeur de listenerFrame ne doit pas être appelé via createSingleton() (ou createSingletonPtr()) et doit être appelé avec un Ogre::Root * en argument!" << std::endl;
}

ListenerFrame::ListenerFrame(Ogre::Root * root) : ClassRootSingleton<ListenerFrame>(), closed(false)
{
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
