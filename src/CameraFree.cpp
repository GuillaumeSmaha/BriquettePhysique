#include "CameraFree.h"


CameraFree::CameraFree(Ogre::String cameraName, Ogre::SceneNode * nodeInit) : CameraAbstract(cameraName)
{
    this->camera->setFixedYawAxis(true);
	this->camera->setOrientation(nodeInit->_getDerivedOrientation());
	this->camera->setPosition(nodeInit->_getDerivedPosition());
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, 500.0));
	this->camera->lookAt(nodeInit->getPosition()+Ogre::Vector3(0.0, 0.0, 10.0));
    //permet de gérer les déplacements de la caméra avec la souris
	PlayerControls::getSingletonPtr()->signalMouseMoved.add(&CameraFree::onMouseMoved, this);
	PlayerControls::getSingletonPtr()->signalKeyPressed.add(&CameraFree::onKeyPressed, this);
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


void CameraFree::onMouseMoved(Ogre::Vector3 mouseVec){
    this->camera->moveRelative(Ogre::Vector3(mouseVec[0], -mouseVec[1], 0));

}


void CameraFree::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::CAM_ZOOM_IN:
            this->camera->moveRelative(Ogre::Vector3(0,0,20));
            break;
        case Controls::CAM_ZOOM_OUT:
            this->camera->moveRelative(Ogre::Vector3(0,0,-20));
            break;
        default:
            break;
    }
}
