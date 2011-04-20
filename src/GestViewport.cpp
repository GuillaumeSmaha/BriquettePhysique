#include "GestViewport.h"

template<> GestViewport * ClassRootSingleton<GestViewport>::_instance = NULL;


GestViewport::GestViewport() : ClassRootSingleton<GestViewport>()
{
}

GestViewport::~GestViewport()
{
	while(this->removeViewport(0)) {};
	ListenerWindow::getSingletonPtr()->getRenderWindow()->removeAllViewports();
}

int GestViewport::addViewport(CameraAbstract * gestCamera)
{
	Ogre::Viewport * viewport = ListenerWindow::getSingletonPtr()->getRenderWindow()->addViewport(gestCamera->getCamera(), this->countViewport());
	viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
	
	this->listViewport.push_back(viewport);
	
	for(int i = 0 ; i < this->countViewport() ; i++)
	{
		Ogre::Real left = viewport->getWidth()/this->countViewport()*i;
		Ogre::Real top = viewport->getTop();
		Ogre::Real width = viewport->getWidth()/this->countViewport();
		Ogre::Real height = viewport->getHeight();
		
		Ogre::Viewport * viewport = this->listViewport.at(i);
		viewport->setDimensions(left, top, width, height);
		viewport->getCamera()->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
	}
	
	return (this->countViewport()-1);
}


bool GestViewport::changeCameraViewport(int idViewport, CameraAbstract * gestCamera)
{
	if(idViewport >= this->countViewport())
	{
		return false;
	}
	
	Ogre::Viewport * viewport = this->listViewport.at(idViewport);
	if(viewport != NULL)
	{
		viewport->setCamera(gestCamera->getCamera());
		gestCamera->getCamera()->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
	
		return true;
	}
	
	return false;
}

bool GestViewport::removeViewport(int idViewport)
{	
	if(idViewport >= this->countViewport())
	{
		return false;
	}
	
	Ogre::Viewport * viewport = this->listViewport.at(idViewport);
		
	this->listViewport.erase(this->listViewport.begin()+idViewport);
	ListenerWindow::getSingletonPtr()->getRenderWindow()->removeViewport(viewport->getZOrder());
	
	if(this->countViewport() > 0)
	{
		for(int i = 0 ; i < this->countViewport() ; i++)
		{
			Ogre::Real left = viewport->getWidth()/this->countViewport()*i;
			Ogre::Real top = viewport->getTop();
			Ogre::Real width = viewport->getWidth()/this->countViewport();
			Ogre::Real height = viewport->getHeight();
			
			Ogre::Viewport * viewport = this->listViewport.at(i);
			viewport->setDimensions(left, top, width, height);
			viewport->getCamera()->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
		}
	}
	
	return true;
}
