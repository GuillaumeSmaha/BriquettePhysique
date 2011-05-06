#include "MouseFunction.h"

MouseFunction::MouseFunction()
{
	
}


MouseFunction::~MouseFunction()
{
	
}


OgreBulletDynamics::RigidBody * MouseFunction::getBodyUnderCursorUsingBullet(Ogre::Ray &rayTo, Ogre::Real mouseScreenX, Ogre::Real mouseScreenY)
{
    Ogre::Camera * curCam = GestCamera::getSingletonPtr()->getCurrentCamera()->getCamera();
        
    rayTo = curCam->getCameraToViewportRay(mouseScreenX, mouseScreenY);
    
    OgreBulletDynamics::DynamicsWorld * world = ListenerCollision::getSingletonPtr()->getWorld();
    
    OgreBulletCollisions::CollisionClosestRayResultCallback *
    mCollisionClosestRayResultCallback = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayTo, world, 5000);
            
    world->launchRay(*mCollisionClosestRayResultCallback);
    std::cout << "ray lauched" << std::endl;
    
    OgreBulletDynamics::RigidBody * bodyResult = NULL;
    
    if (mCollisionClosestRayResultCallback->doesCollide ())
    {
         bodyResult = static_cast<OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallback->getCollidedObject());
    }
    delete mCollisionClosestRayResultCallback;
    
    return bodyResult;
}

OgreBulletCollisions::CollisionClosestRayResultCallback * MouseFunction::getResultUnderCursorUsingBullet(Ogre::Ray &rayTo, Ogre::Real mouseScreenX, Ogre::Real mouseScreenY)
{
    Ogre::Camera * curCam = GestCamera::getSingletonPtr()->getCurrentCamera()->getCamera();
    
    rayTo = curCam->getCameraToViewportRay(mouseScreenX, mouseScreenY);
    
    OgreBulletDynamics::DynamicsWorld * world = ListenerCollision::getSingletonPtr()->getWorld();
    
    OgreBulletCollisions::CollisionClosestRayResultCallback *
    mCollisionClosestRayResultCallback = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayTo, world, 5000);
            
    world->launchRay(*mCollisionClosestRayResultCallback);
    
    return mCollisionClosestRayResultCallback;
}
