#include "CameraFree.h"


CameraFree::CameraFree(Ogre::String cameraName, Ogre::SceneNode * nodeInit) : CameraAbstract(cameraName)
{
    centre=Ogre::Vector3(0,0,0);
    nodeInit->attachObject(this->camera);
    this->camera->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);
    this->camera->setPosition(0,0,0);
    this->camera->setOrientation(Ogre::Quaternion(1,0,0,0));

	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, 500.0));
    //permet de gérer les déplacements de la caméra avec la souris

    this->camera->setAutoTracking(true, GestObj::getSingletonPtr()->getTable()->getNode());

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

    Ogre::Vector3 oldPos= this->camera->getPosition();
    double dist= this->camera->getPosition().distance(centre);
    this->camera->setPosition(centre);

    this->camera->yaw(Ogre::Degree(mouseVec[0] * 0.25f));
    this->camera->pitch(Ogre::Degree(mouseVec[1] * 0.25f));

    this->camera->moveRelative(Ogre::Vector3(centre.x, centre.y, dist));

    //permet d'empecher de passer derriere la table
    double z= this->camera->getPosition().z;
    if(z<30){   
        this->camera->setPosition(oldPos);
    }
}


void CameraFree::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::CAM_ZOOM_IN:
            this->camera->moveRelative(Ogre::Vector3(0,0,-20));
            break;
        case Controls::CAM_ZOOM_OUT:
            this->camera->moveRelative(Ogre::Vector3(0,0,20));
            break;
        case Controls::CAM_ROTATE_LEFT:{
            //manuallyRotate(Ogre::Radian(PI/36));
            break;
        }
        case Controls::CAM_ROTATE_RIGHT:{
            //manuallyRotate(Ogre::Radian(-PI/36));
            break;
        }
        default:
            break;
    }
}


void CameraFree::manuallyRotate(Ogre::Radian angle){
    Ogre::Vector3 pos= Ogre::Vector3(this->camera->getPosition().x, this->camera->getPosition().y , this->camera->getPosition().z);
    double cosxprim= pos.x* Ogre::Math::Cos(angle);
    double sinxprim= pos.y* Ogre::Math::Sin(angle);
    double xprim= cosxprim- sinxprim;
    double sinyprim= pos.x*Ogre::Math::Sin(angle);
    double cosyprim= pos.y*Ogre::Math::Cos(angle);
    double yprim=sinyprim+ cosyprim;
    this->camera->setPosition(Ogre::Vector3(xprim, yprim, this->camera->getPosition().z));
    this->camera->lookAt(Ogre::Vector3(0.0, 0.0, 0.0));

}
