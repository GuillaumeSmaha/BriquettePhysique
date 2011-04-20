#include "GestCamera.h"

template<> GestCamera * ClassRootSingleton<GestCamera>::_instance = NULL;

GestCamera::GestCamera() : ClassRootSingleton<GestCamera>()
{
}

GestCamera::~GestCamera()
{
	while(this->removeCamera(0)) {};
}

void GestCamera::addCamera(CameraAbstract * camera)
{
    this->listCameras.push_back(camera);
}


CameraAbstract * GestCamera::addCamera(CameraAbstract::CameraType cameraType, Ogre::String cameraName, Ogre::SceneNode * targetNode)
{
	CameraAbstract * cam = NULL;
	switch(cameraType)
	{
		case CameraAbstract::CAMERA_FREE :
			cam = new CameraTarget(cameraName, targetNode);
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
	if(id >= this->listCameras.size())
	{
		return false;
	}
	
	CameraAbstract * cam = this->listCameras.at(id);
	this->listCameras.erase(this->listCameras.begin()+id);
	delete cam;
	
	return true;
}

CameraAbstract * GestCamera::getCamera(unsigned int id)
{
    if(id >= this->listCameras.size())
    {
        return NULL;
    }
    return this->listCameras.at(id);
}
