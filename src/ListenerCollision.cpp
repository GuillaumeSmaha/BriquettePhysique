#include "ListenerCollision.h"

template<> ListenerCollision * ClassRootSingleton<ListenerCollision>::_instance = NULL;

ListenerCollision::ListenerCollision() : ClassRootSingleton<ListenerCollision>(), physicEngineState(true), physicEngineMutex(false), physicEngineMutexLocker(NULL)
{	
    //Start Bullet
    mWorld = new OgreBulletDynamics::DynamicsWorld(GestSceneManager::getSceneManager(), Ogre::AxisAlignedBox(Ogre::Vector3 (-1, -1, -1), Ogre::Vector3 (1,  1,  1)), Ogre::Vector3(0,0,-9.81));
    //add Debug info display tool
    debugDrawer = new OgreBulletCollisions::DebugDrawer();
    debugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
    mWorld->setDebugDrawer(debugDrawer);
    mWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers
    Ogre::SceneNode *node_debugDrawer = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
    node_debugDrawer->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));
    mWorld->getBulletDynamicsWorld()->clearForces();

    ListenerFrame::getSingletonPtr()->signalFrameStarted.add(&ListenerCollision::updateCollision, this);    
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&ListenerCollision::onKeyPressed, this);
}

ListenerCollision::~ListenerCollision()
{
    delete mWorld->getDebugDrawer();
    mWorld->setDebugDrawer(0);
    delete mWorld;
}


void ListenerCollision::updateCollision(const Ogre::FrameEvent &evt)
{
	if(this->physicEngineState)
		mWorld->stepSimulation(evt.timeSinceLastFrame);   // update Bullet Physics animation
}

void ListenerCollision::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::SWITCH_BULLET_STATE:
            this->switchPhysicEngineState();
            break;
            
        default:
            break;
    }
}


bool ListenerCollision::physicEngineMutexLock(void * locker)
{
	if(locker != NULL)
	{
		if(this->physicEngineMutex == true)
		{
			std::cerr << "Mutex physic engine is already locked !" << std::endl;
		}
		else
		{
			this->physicEngineMutexLocker = locker;
			this->physicEngineMutex = true;
			return true;
		}
	}
	
	return false;
}


void ListenerCollision::physicEngineMutexUnLock(void * locker)
{
	if(locker != NULL && locker == this->physicEngineMutexLocker)
	{
		this->physicEngineMutex = false;
	}
}


bool ListenerCollision::switchPhysicEngineState(void * locker)
{
	bool result;
	
	if(this->physicEngineState)
		result = this->setPhysicEngineState(false, locker);
	else
		result = this->setPhysicEngineState(true, locker);
			
	return result;
}


bool ListenerCollision::setPhysicEngineState(bool physicEngineState, void * locker)
{
	if(this->physicEngineMutex == false || (this->physicEngineMutex == true && locker == this->physicEngineMutexLocker))
	{
		this->physicEngineState = physicEngineState;
		
		if(Menus::getSingletonPtr()->getMenusBriquette() != NULL)
			Menus::getSingletonPtr()->getMenusBriquette()->updateTextButtons();
			
		return true;
	}
		
	return false;
}
