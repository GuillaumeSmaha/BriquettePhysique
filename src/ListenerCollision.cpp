#include "ListenerCollision.h"



ListenerCollision * ListenerCollision::_instance = NULL;

void ListenerCollision::createSingleton()
{
	if (_instance == NULL)
	{
		if(Application::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerCollision();
		}
	}
}

ListenerCollision * ListenerCollision::getSingletonPtr()
{
	if (_instance == NULL)
	{
		if(Application::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerCollision();
		}
	}
	return _instance;
}

ListenerCollision & ListenerCollision::getSingleton()
{
	if (_instance == NULL)
	{
		if(Application::getSingletonPtr()->getInputManager() != NULL)
		{
			_instance = new ListenerCollision();
		}
	}
	return *_instance;
}

void ListenerCollision::destroySingleton()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}

ListenerCollision::ListenerCollision()
{	
    //Start Bullet
    mWorld = new OgreBulletDynamics::DynamicsWorld(GestSceneManager::getSceneManager(), Ogre::AxisAlignedBox(Ogre::Vector3 (-1, -1, -1), Ogre::Vector3 (1,  1,  1)), Ogre::Vector3(0,0,0));
    //add Debug info display tool
    debugDrawer = new OgreBulletCollisions::DebugDrawer();
    debugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
    mWorld->setDebugDrawer(debugDrawer);
    mWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers
    Ogre::SceneNode *node_debugDrawer = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
    node_debugDrawer->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));
    mWorld->getBulletDynamicsWorld()->clearForces();

    ListenerFrame::getSingletonPtr()->signalFrameStarted.add(&ListenerCollision::updateCollision, this);
    //listenerFrame->signalFrameEnded.add(&ListenerCollision::updateCollision, this);

}

ListenerCollision::~ListenerCollision()
{
    delete mWorld->getDebugDrawer();
    mWorld->setDebugDrawer(0);
    delete mWorld;
}

void ListenerCollision::updateCollision(const Ogre::FrameEvent &evt)
{

}
