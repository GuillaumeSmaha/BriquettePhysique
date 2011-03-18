#include "GestViewport.h"


GestViewport * GestViewport::_instance = NULL;


void GestViewport::createSingleton()
{
	if (_instance == NULL)
	{
		_instance = new GestViewport();
	}
}

GestViewport * GestViewport::getSingletonPtr()
{
	if (_instance == NULL)
	{
		_instance = new GestViewport();
	}
	return _instance;
}

GestViewport & GestViewport::getSingleton()
{
	if (_instance == NULL)
	{
		_instance = new GestViewport();
	}
	return *_instance;
}

void GestViewport::destroySingleton()
{
    if(_instance != NULL)
    {
		ListenerWindow::getSingletonPtr()->getRenderWindow()->removeAllViewports();
		while(_instance->removeViewport(0)) {};
        delete _instance;
    }
}

GestViewport::GestViewport()
{
	if (_instance == NULL)
	{
		_instance = this;
	}
}

GestViewport::~GestViewport()
{
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
	if(idViewport < this->countViewport())
	{
		Ogre::Viewport * viewport = this->listViewport.at(idViewport);
		if(viewport != NULL)
		{
			viewport->setCamera(gestCamera->getCamera());
			gestCamera->getCamera()->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
		
			return true;
		}
	}
	return false;
}

bool GestViewport::removeViewport(int idViewport)
{
	if(idViewport < this->countViewport())
	{
		Ogre::Viewport * viewport = this->listViewport.at(idViewport);
		if(viewport != NULL)
		{
			this->listViewport.erase(this->listViewport.begin()+idViewport);
			delete viewport;
			
			
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
			
			return true;
		}
	}
	
	return false;
}
