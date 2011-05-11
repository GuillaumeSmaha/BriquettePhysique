#include "CameraTarget.h"


CameraTarget::CameraTarget(CameraAbstract::CameraType cameraType, Ogre::String cameraName, Ogre::SceneNode * targetNode) : CameraAbstract(cameraType, cameraName)
{
    this->targetNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_CAMERA)->createChildSceneNode("nodeTargetCamera_"+cameraName+"_"+Utils::toString(Utils::unique()));
    this->targetNode->_setDerivedPosition(targetNode->_getDerivedPosition());
    this->targetPosition = this->targetNode->_getDerivedPosition();
   
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
    this->camera->setAutoTracking(true, this->targetNode);
    
    
    this->keyPressedMoveTargetX = Controls::NONE;
    this->keyPressedMoveTargetY = Controls::NONE;
    

	PlayerControls::getSingletonPtr()->signalMouseMoved.add(&CameraTarget::onMouseMoved, this);
	PlayerControls::getSingletonPtr()->signalKeyPressed.add(&CameraTarget::onKeyPressed, this);
	PlayerControls::getSingletonPtr()->signalKeyReleased.add(&CameraTarget::onKeyReleased, this);
	
	ListenerFrame::getSingletonPtr()->signalFrameRendering.add(&CameraTarget::update_camera, this);
}


CameraTarget::~CameraTarget()
{
	PlayerControls::getSingletonPtr()->signalMouseMoved.remove(&CameraTarget::onMouseMoved, this);
	PlayerControls::getSingletonPtr()->signalKeyPressed.remove(&CameraTarget::onKeyPressed, this);
	PlayerControls::getSingletonPtr()->signalKeyReleased.remove(&CameraTarget::onKeyReleased, this);
	
	ListenerFrame::getSingletonPtr()->signalFrameRendering.remove(&CameraTarget::update_camera, this);
	
	this->nodeCamera->detachObject(this->camera);
	GestSceneManager::getSceneManager()->destroySceneNode(this->nodeCamera);
	GestSceneManager::getSceneManager()->destroySceneNode(this->targetNode);
}
		
void CameraTarget::init_camera()
{
	this->targetPosition = this->targetNode->_getDerivedPosition();
}
		
void CameraTarget::update_camera()
{
}
		
void CameraTarget::update_camera(void * null)
{
	Ogre::Vector3 vec = (this->targetPosition - this->targetNode->_getDerivedPosition());
	Ogre::Real dist = vec.length();
	
	if(dist > 1.0)
	{
		vec.normalise();
		this->moveTarget(vec);
	}
	
	switch(this->keyPressedMoveTargetX)
	{
        case Controls::CAM_TARGET_MOVE_LEFT :
			this->targetPosition += Ogre::Vector3(0.0, -1.0, 0.0);
            break;
        
        case Controls::CAM_TARGET_MOVE_RIGHT :
			this->targetPosition += Ogre::Vector3(0.0, 1.0, 0.0);
            break;
        
        default:
            break;
	}
	
	switch(this->keyPressedMoveTargetY)
	{
        case Controls::CAM_TARGET_MOVE_UP :
			this->targetPosition += Ogre::Vector3(1.0, 0.0, 0.0);
            break;
                    
        case Controls::CAM_TARGET_MOVE_DOWN :
			this->targetPosition += Ogre::Vector3(-1.0, 0.0, 0.0);
            break;
        
        default:
            break;
	}

}


void CameraTarget::onMouseMoved(MouseMove_t &mouseMove)
{    
	if(mouseMove.controlMouseId == Controls::MOUSE_CAMERA_ROTATE)
	{
		Ogre::Degree yaw = Ogre::Degree(mouseMove.vector[0] * 0.25f);
		Ogre::Degree pitch = Ogre::Degree(mouseMove.vector[1] * 0.25f);
		
		if(this->checkRotation(yaw, pitch))
		{			
			Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
			
			this->camera->setPosition(this->targetNode->_getDerivedPosition());

			this->camera->yaw(yaw);
			this->camera->pitch(pitch);
			
			this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, dist));
		}
	}
	else if(mouseMove.controlMouseId == Controls::MOUSE_CAMERA_ZOOM)
	{
		this->zoom((mouseMove.vector[0]+mouseMove.vector[1])/2.0);
	}
	else if(abs(mouseMove.vector[2]) > 1.0)
		this->zoom(-mouseMove.vector[2]/6.0);
}


void CameraTarget::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::CAM_ZOOM_IN :
            this->zoom(-20.0);
            break;
            
        case Controls::CAM_ZOOM_OUT :
            this->zoom(20.0);
            break;
            
        case Controls::CAM_ROTATE_LEFT :
            this->manuallyRotate(Ogre::Radian(PI/36.0));
            break;
        
        case Controls::CAM_ROTATE_RIGHT :
            this->manuallyRotate(Ogre::Radian(-PI/36.0));
            break;
        
        case Controls::CAM_TARGET_MOVE_LEFT :
        case Controls::CAM_TARGET_MOVE_RIGHT :
			this->setKeyPressedMoveTargetX(key);
            break;
            
        case Controls::CAM_TARGET_MOVE_UP :
        case Controls::CAM_TARGET_MOVE_DOWN :
			this->setKeyPressedMoveTargetY(key);
            break;
        
        default:
            break;
    }
    
}


void CameraTarget::onKeyReleased(Controls::Controls key)
{
	if(this->keyPressedMoveTargetX == key)
		this->keyPressedMoveTargetX = Controls::NONE;
		
	if(this->keyPressedMoveTargetY == key)
		this->keyPressedMoveTargetY = Controls::NONE;
}


void CameraTarget::manuallyRotate(Ogre::Radian angle)
{
    Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
    this->camera->setPosition(this->targetNode->_getDerivedPosition());
    this->camera->yaw(angle);
    this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, dist));
}


void CameraTarget::zoom(Ogre::Real zoomDist)
{
	Ogre::Real distMin = 25.0;
    Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
    
    if((dist < distMin && zoomDist > 0) || (dist >= distMin && (dist+zoomDist) > distMin))
    {
		this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, zoomDist));
	}
}


void CameraTarget::definePositionTarget(Ogre::Vector3 vector)
{
	this->targetPosition = vector;
}


bool CameraTarget::checkRotation(Ogre::Degree yaw, Ogre::Degree pitch)
{
	Ogre::Real distZ = this->camera->getPosition()[2] - this->targetNode->_getDerivedPosition()[2];
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	Ogre::Real seuil = 10.0 + abs(distZ / 50.0);
		
	if((distZ >= 0 && (distZ+seuil) > dist && pitch.valueDegrees() <= 0.0)
		|| (distZ < 0 && (distZ-seuil) < -dist && pitch.valueDegrees() > 0.0))
		return false;
	
	return true;
}


void CameraTarget::moveTarget(Ogre::Vector3 vector)
{
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	Ogre::Vector3 vec = this->targetNode->getPosition() + vector;
	this->targetNode->setPosition(vec);
	Ogre::Real newDist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	this->zoom(dist-newDist);
}


Controls::Controls CameraTarget::getKeyPressedMoveTargetX()
{
	return this->keyPressedMoveTargetX;
}

void CameraTarget::setKeyPressedMoveTargetX(Controls::Controls keyPressedMoveTargetX)
{
	this->keyPressedMoveTargetX = keyPressedMoveTargetX;
}


Controls::Controls CameraTarget::getKeyPressedMoveTargetY()
{
	return this->keyPressedMoveTargetY;
}

void CameraTarget::setKeyPressedMoveTargetY(Controls::Controls keyPressedMoveTargetY)
{
	this->keyPressedMoveTargetY = keyPressedMoveTargetY;
}


Ogre::SceneNode * CameraTarget::getTargetNode()
{
	return this->targetNode;
}
