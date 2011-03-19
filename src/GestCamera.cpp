#include "GestCamera.h"


GestCamera * GestCamera::_instance = NULL;


void GestCamera::createSingleton()
{
	if (_instance == NULL)
	{
		_instance = new GestCamera();
	}
}

GestCamera * GestCamera::getSingletonPtr()
{
	if (_instance == NULL)
	{
		_instance = new GestCamera();
	}
	return _instance;
}

GestCamera & GestCamera::getSingleton()
{
	if (_instance == NULL)
	{
		_instance = new GestCamera();
	}
	return *_instance;
}

void GestCamera::destroySingleton()
{
    if(_instance != NULL)
    {
		while(_instance->removeCamera(0)) {};
        delete _instance;
    }
}

GestCamera::GestCamera()
{
	if (_instance == NULL)
	{
		_instance = this;
	}
}

GestCamera::~GestCamera()
{
}


void GestCamera::addCamera(CameraAbstract * camera)
{
    this->listCameras.push_back(camera);
}


CameraAbstract * GestCamera::addCamera(CameraAbstract::CameraType cameraType, Ogre::String cameraName)
{
	CameraAbstract * cam = NULL;
	switch(cameraType)
	{
		case CameraAbstract::CAMERA_FREE :
			cam = new CameraFree(cameraName, GestSceneManager::getSceneManager()->getRootSceneNode());
			this->listCameras.push_back(cam);
			break;
			
		default:
			break;
	}
	
	return cam;
}


bool GestCamera::removeCamera(CameraAbstract * cam)
{
	for(unsigned int i = 0; i < this->listCameras.size() ; i++)
	{
		if(this->listCameras[i] == cam)
		{
			delete cam;
			this->listCameras.erase(this->listCameras.begin()+i);
			return true;
		}
	}
	
	return false;
}

bool GestCamera::removeCamera(unsigned int id)
{
	if(id > this->listCameras.size())
	{
		return false;
	}
	
	CameraAbstract * cam = this->listCameras.at(id);
	delete cam;
	this->listCameras.erase(this->listCameras.begin()+id);
	
	return true;
}

CameraAbstract * GestCamera::getCamera(unsigned int id)
{
    if(id > this->listCameras.size())
    {
        return NULL;
    }
    return this->listCameras.at(id);
}
