#include "CameraFree.h"


CameraFree::CameraFree(Ogre::String cameraName, Ogre::SceneNode * nodeInit) : CameraAbstract(cameraName)
{
    this->camera_x=0;
    this->camera_y=0;
    this->camera->setFixedYawAxis(true);
	//this->camera->setOrientation(nodeInit->_getDerivedOrientation());
	//this->camera->setPosition(nodeInit->_getDerivedPosition());
    this->camera->setPosition(0,0,0);
    this->camera->setOrientation(Ogre::Quaternion(1,0,0,0));

    //this->camera->yaw(Ogre::Radian(180));
    //this->camera->pitch(Ogre::Radian(-15));
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, 500.0));
	//this->camera->lookAt(nodeInit->getPosition()+Ogre::Vector3(0.0, 0.0, 1.0));
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
//    camera_x += mouseVec[0]/100;
//    camera_y += mouseVec[1]/100;
//    Ogre::Vector3 pos_player = GestObj::getSingletonPtr()->getTable()->getNode()->getPosition();
//    Ogre::Vector3 pos_camera= this->camera->getPosition();
//    pos_camera.x= pos_player.x + (DISTANCE_CAMERA* cos(camera_x));
//    pos_camera.y= pos_player.y + (DISTANCE_CAMERA* cos(camera_y));
//    pos_camera.z= pos_player.z + (DISTANCE_CAMERA* sin(camera_x)* sin(camera_y));
//    
//    this->camera->setPosition(pos_camera);
//    this->camera->lookAt(pos_player.x, pos_player.y + 1, pos_player.z);
//
    Ogre::Vector3 oldPos= this->camera->getPosition();
    double dist= this->camera->getPosition().distance(Ogre::Vector3(0,0,0));
    this->camera->setPosition(GestObj::getSingletonPtr()->getTable()->getNode()->_getDerivedPosition());

    this->camera->yaw(Ogre::Degree(mouseVec[0] * 0.25f));
    this->camera->pitch(Ogre::Degree(mouseVec[1] * 0.25f));

    this->camera->moveRelative(Ogre::Vector3(0, 0, dist));

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
            this->camera->moveRelative(Ogre::Vector3(0,0,20));
            break;
        case Controls::CAM_ZOOM_OUT:
            this->camera->moveRelative(Ogre::Vector3(0,0,-20));
            break;
        case Controls::CAM_ROTATE_LEFT:{
            Ogre::Radian angle=Ogre::Radian(PI/36);
            //double dist= this->camera->getPosition().distance(Ogre::Vector3(0,0,0));
            //double hypo= dist/Ogre::Math::Cos(angle);
            //Ogre::Vector3 crossPd= this->camera->getPosition().crossProduct(Ogre::Vector3(0,0,1);
            //std::cout<<"crossPd"<<crossPd<<std::endl;
            //this->setPosition(crossPd*hypo);
            std::cout<<"pos : "<<this->camera->getPosition()<<std::endl;
            //Ogre::Vector3 pos= this->camera->getPosition();
            //Ogre::Vector3 pos= Ogre::Vector3(100, -92, this->camera->getPosition().z);
            Ogre::Vector3 pos= Ogre::Vector3(this->camera->getPosition().x, this->camera->getPosition().y , this->camera->getPosition().z);
            //double cosxprim= this->camera->getPosition().x * Ogre::Math::Cos(angle);
            //double sinxprim= this->camera->getPosition().y * Ogre::Math::Sin(angle);
            double cosxprim= pos.x* Ogre::Math::Cos(angle);
            double sinxprim= pos.y* Ogre::Math::Sin(angle);


            double xprim= cosxprim- sinxprim;
            //double yprim= this->camera->getPosition().x* Ogre::Math::Sin(angle) + this->camera->getPosition().y * Ogre::Math::Cos(angle);
            double sinyprim= pos.x*Ogre::Math::Sin(angle);
            double cosyprim= pos.y*Ogre::Math::Cos(angle);
            double yprim=sinyprim+ cosyprim;
            this->camera->setPosition(Ogre::Vector3(xprim, yprim, this->camera->getPosition().z));
            //this->camera->lookAt(Ogre::Vector3(0.0, 0.0, 0.0));
            break;
        }
        case Controls::CAM_ROTATE_RIGHT:
            this->camera->rotate(Ogre::Vector3(1,0,0), Ogre::Radian(-PI/10));

            break;
        default:
            break;
    }
}
