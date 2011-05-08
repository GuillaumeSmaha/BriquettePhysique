#include "MouseFunction.h"


template<> MouseFunction * ClassRootSingleton<MouseFunction>::_instance = NULL;


void MouseFunction::createSingleton()
{
    std::cerr << "Le constructeur de MouseFunction ne doit pas être appelé via \
        createSingleton() et doit être appelé avec un Ogre::RenderWindow * en argument \
        !" << std::endl << "Attention le singleton n'ayant pas été crée, il est fort \
        possible d'avoir des erreurs de segmentation"  << std::endl ;
}

void MouseFunction::createSingleton(Ogre::RenderWindow * win)
{
    new MouseFunction(win);
}


MouseFunction::MouseFunction()
{
	
}


MouseFunction::MouseFunction(Ogre::RenderWindow * win) : ClassRootSingleton<MouseFunction>()
{
	this->winWidth = win->getWidth();
	this->winHeight = win->getHeight();

	//la souris est centré initialement
	this->posMouse[0] = 0.5;        //correspond à la position horizontale
	this->posMouse[1] = 0.5;        //correspond à la position verticale
}


MouseFunction::~MouseFunction()
{
	
}



void MouseFunction::injectMouseMove(float delta_x, float delta_y)
{
	//réglage horizontal
	this->posMouse[0] = this->posMouse[0] + (delta_x / this->winWidth);

	//Ces conditions permettent d'éviter que la souris ne sorte de la fenetre
	//C'est nécéssaire car la souris CEGUI est prévu pour ne pas sortir de la fenetre, 
	//on perd donc la correspondance si l'une sort et pas l'autre
	if(this->posMouse[0] < (0.0))
	{
		this->posMouse[0] = 0.0;
	}
	if(this->posMouse[0] > (1.0))
	{
		this->posMouse[0] = 1.0;
	}

	//réglage vertical
	this->posMouse[1] = this->posMouse[1] + (delta_y / this->winHeight);

	//Ces conditions permettent d'éviter que la souris ne sorte de la fenetre
	//C'est nécéssaire car la souris CEGUI est prévu pour ne pas sortir de la fenetre, 
	//on perd donc la correspondance si l'une sort et pas l'autre
	if(this->posMouse[1] < (0.0))
	{
		this->posMouse[1] = 0.0;
	}
	if(this->posMouse[1] > (1.0))
	{
		this->posMouse[1] = 1.0;
	}
}

OgreBulletDynamics::RigidBody * MouseFunction::getBodyUnderCursorUsingBullet(Ogre::Ray &rayTo)
{
    Ogre::Real mouseScreenX = this->posMouse[0];
    Ogre::Real mouseScreenY = this->posMouse[1];    
    
    return MouseFunction::getBodyUnderCursorUsingBullet(rayTo, mouseScreenX, mouseScreenY);
}


OgreBulletCollisions::CollisionClosestRayResultCallback * MouseFunction::getResultUnderCursorUsingBullet(Ogre::Ray &rayTo)
{
    Ogre::Real mouseScreenX = this->posMouse[0];
    Ogre::Real mouseScreenY = this->posMouse[1]; 
   
    return MouseFunction::getResultUnderCursorUsingBullet(rayTo, mouseScreenX, mouseScreenY);
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

