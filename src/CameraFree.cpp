#include "CameraFree.h"


CameraFree::CameraFree(Ogre::String cameraName, Ogre::SceneNode * nodeInit) : CameraAbstract(cameraName)
{
    this->camera->setFixedYawAxis(true);
	this->camera->setOrientation(nodeInit->_getDerivedOrientation());
	this->camera->setPosition(nodeInit->_getDerivedPosition());
	this->camera->moveRelative(Ogre::Vector3(-1000.0, 0.0, 1000.0));
	this->camera->lookAt(nodeInit->getPosition()+Ogre::Vector3(0.0, 0.0, 10.0));
}
		
void CameraFree::init_camera()
{
	/*
	this->camera->setPosition(Ogre::Vector3(100, 100, -500));
	this->camera->lookAt(this->sceneMgr->getRootSceneNode()->getPosition());
	this->camera->setOrientation(Ogre::Quaternion(0, 0, 0, 1));
	*/

}
		
void CameraFree::update_camera()
{
}
