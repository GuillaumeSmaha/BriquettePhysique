#include "CameraTarget.h"


CameraTarget::CameraTarget(Ogre::String cameraName, Ogre::SceneNode * targetNode) : CameraAbstract(cameraName)
{
    this->targetNode = targetNode;
    this->nodeCamera = targetNode->createChildSceneNode("nodeCamera_"+cameraName+"_"+Utils::toString(Utils::unique()));
    this->nodeCamera->setOrientation(Ogre::Quaternion(0.0, 0.0, 0.0, 1.0));
    this->nodeCamera->setPosition(0.0, 0.0, 0.0);
    this->nodeCamera->pitch(Ogre::Degree(-50));
    this->nodeCamera->attachObject(this->camera);
    
    this->camera->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);
    this->camera->setPosition(0.0, 0.0, 0.0);

	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, 500.0));

    this->camera->lookAt(this->targetNode->getPosition());
    
    this->camera->setAutoTracking(true, targetNode);

	PlayerControls::getSingletonPtr()->signalMouseCameraMoved.add(&CameraTarget::onMouseMoved, this);
	PlayerControls::getSingletonPtr()->signalKeyPressed.add(&CameraTarget::onKeyPressed, this);
}
		
void CameraTarget::init_camera()
{
	/*
	this->camera->setPosition(Ogre::Vector3(100, 100, -500));
	this->camera->lookAt(this->sceneMgr->getRootSceneNode()->getPosition());
	this->camera->setOrientation(Ogre::Quaternion(0, 0, 0, 1));
	*/

}
		
void CameraTarget::update_camera()
{
}


void CameraTarget::onMouseMoved(Ogre::Vector3 mouseVec)
{
	/*Ogre::Vector3 posTarget = this->targetNode->getPosition();
    Ogre::Vector3 oldPos = this->camera->getPosition();
    double dist = this->camera->getPosition().distance(posTarget);
    this->camera->setPosition(posTarget);

    this->camera->yaw(Ogre::Degree(mouseVec[0] * 0.25f));
    this->camera->pitch(Ogre::Degree(mouseVec[1] * 0.25f));
    

    this->camera->moveRelative(Ogre::Vector3(posTarget.x, posTarget.y, dist));

    //permet d'empecher de passer derriere la table
    double z = this->camera->getPosition().z;
    if(z < 30)
    {   
        this->camera->setPosition(oldPos);
    }
    */
    
	this->nodeCamera->yaw(Ogre::Degree(mouseVec[0] * 0.25f));
	
    if(this->checkRotation(mouseVec[1] * 0.25f))
    {
		this->nodeCamera->pitch(Ogre::Degree(mouseVec[1] * 0.25f));
    }
}


void CameraTarget::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::CAM_ZOOM_IN :
            this->camera->moveRelative(Ogre::Vector3(0,0,-20));
            break;
            
        case Controls::CAM_ZOOM_OUT :
            this->camera->moveRelative(Ogre::Vector3(0,0,20));
            break;
            
        case Controls::CAM_ROTATE_LEFT :
        {
            this->manuallyRotate(Ogre::Radian(PI/36));
            break;
        }
        
        case Controls::CAM_ROTATE_RIGHT :
        {
            this->manuallyRotate(Ogre::Radian(-PI/36));
            break;
        }
        
        default:
            break;
    }
}


void CameraTarget::manuallyRotate(Ogre::Radian angle)
{
    //~ Ogre::Vector3 pos = Ogre::Vector3(this->camera->getPosition().x, this->camera->getPosition().y , this->camera->getPosition().z);
    //~ double cosxprim = pos.x* Ogre::Math::Cos(angle);
    //~ double sinxprim = pos.y* Ogre::Math::Sin(angle);
    //~ double xprim = cosxprim- sinxprim;
    //~ double sinyprim = pos.x*Ogre::Math::Sin(angle);
    //~ double cosyprim = pos.y*Ogre::Math::Cos(angle);
    //~ double yprim = sinyprim+ cosyprim;
    //~ this->camera->setPosition(Ogre::Vector3(xprim, yprim, this->camera->getPosition().z));
    //~ this->camera->lookAt(this->targetNode->getPosition());
    if(this->checkRotation(angle.valueDegrees()))
    {
		this->nodeCamera->yaw(angle);
    }
}


bool CameraTarget::checkRotation(Ogre::Real angleRotation)
{
	Ogre::Quaternion orientation = this->nodeCamera->getOrientation();
	Ogre::Real angle = orientation.getPitch().valueDegrees();
	Ogre::Real angleYaw = orientation.getYaw().valueDegrees();
	
	std::cout << "pitch = " << angle << std::endl;
	
	
	if(angle < -160 && angleRotation > 0 || (angle-angleRotation < -160))
	{
		return false;
	}
	else if(angle > -20 && angleRotation < 0 || (angle-angleRotation) > -20)
	{
		return false;
	}
	
	return true;	
}
