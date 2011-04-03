#include "CameraTarget.h"


CameraTarget::CameraTarget(Ogre::String cameraName, Ogre::SceneNode * targetNode) : CameraAbstract(cameraName)
{
    this->targetNode = targetNode;
    
    this->nodeCamera = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA)->createChildSceneNode("nodeCamera_"+cameraName+"_"+Utils::toString(Utils::unique()));
    this->nodeCamera->attachObject(this->camera);

	this->camera->setNearClipDistance(1);
	this->camera->setFarClipDistance(1000);

	// enable infinite far clip distance if we can
	if (Ogre::Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
		this->camera->setFarClipDistance(0);   

	// set the position ant rotation of the camera to look at the target
	this->camera->setPosition(this->targetNode->_getDerivedPosition());
	this->camera->setOrientation(this->targetNode->_getDerivedOrientation());
	this->camera->yaw(Ogre::Radian(180));
	this->camera->pitch(Ogre::Radian(-15));
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, 500.0));


    this->camera->setFixedYawAxis(true, Ogre::Vector3::UNIT_Z);    
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
    Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
    this->camera->setPosition(this->targetNode->_getDerivedPosition());

    this->camera->yaw(Ogre::Degree(mouseVec[0] * 0.25f));
    this->camera->pitch(Ogre::Degree(mouseVec[1] * 0.25f));
    this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, dist));
}


void CameraTarget::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::CAM_ZOOM_IN :
            this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, -20.0));
            break;
            
        case Controls::CAM_ZOOM_OUT :
            this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, 20.0));
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
    Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
    this->camera->setPosition(this->targetNode->_getDerivedPosition());
    this->camera->yaw(angle);
    this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, dist));
}


bool CameraTarget::checkRotation(Ogre::Real angleRotation)
{
	/*Ogre::Quaternion orientation = this->nodeCamera->getOrientation();
	Ogre::Real angle = orientation.getPitch().valueDegrees();
	Ogre::Real angleYaw = orientation.getYaw().valueDegrees();
	
	std::cout << "pitch = " << angle << "yaw = " << angleYaw << std::endl;
	
	
	if(angle < -160 && angleRotation > 0 || (angle-angleRotation < -160))
	{
		return false;
	}
	else if(angle > -20 && angleRotation < 0 || (angle-angleRotation) > -20)
	{
		return false;
	}*/
	
	return true;	
}
