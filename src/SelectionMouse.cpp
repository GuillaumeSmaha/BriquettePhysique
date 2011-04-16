#include "SelectionMouse.h"

using namespace Ogre;

template<> SelectionMouse * ClassRootSingleton<SelectionMouse>::_instance = NULL;


void SelectionMouse::createSingleton()
{
    std::cerr << "Le constructeur de SelectionMouse ne doit pas être appelé via \
        createSingleton() et doit être appelé avec un Ogre::RenderWindow * en argument \
        !" << std::endl << "Attention le singleton n'ayant pas été crée, il est fort \
        possible d'avoir des erreurs de segmentation"  << std::endl ;
}

void SelectionMouse::createSingleton(Ogre::RenderWindow * win)
{
    new SelectionMouse(win);
}



SelectionMouse::SelectionMouse(Ogre::RenderWindow * win) : ClassRootSingleton<SelectionMouse>()
{
    createOverlay(win);
    this->selectedBriquetteOnMove = NULL;   
    this->selectedBriquettePrevious = NULL;   
    PlayerControls::getSingletonPtr()->signalMouseMoved.add(&SelectionMouse::onMouseMoved, this);
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&SelectionMouse::onKeyPressed, this);
    PlayerControls::getSingletonPtr()->signalKeyReleased.add(&SelectionMouse::onKeyReleased, this);
}


SelectionMouse::~SelectionMouse()
{


}


void SelectionMouse::createOverlay(Ogre::RenderWindow * win)
{
	this->mouseOverlay = OverlayManager::getSingletonPtr()->create("GuiOverlay");
	this->mouseOverlay->setZOrder(600);
	this->mousePanel = (Ogre::OverlayElement *)OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIMouse");
	//this->mousePanel->setMaterialName("TargetSights");

	TexturePtr mouseTex = TextureManager::getSingleton().load("target.png", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	this->winWidth= win->getWidth();
	this->winHeight= win->getHeight();
	this->mousePanel->setWidth (mouseTex->getWidth() / (float)this->winWidth); 
	this->mousePanel->setHeight (mouseTex->getHeight() / (float)this->winHeight);

	//la souris est centré initialement
	this->posMouse[0] = 0.5-mousePanel->getWidth()/2;        //correspond à la position horizontale
	this->posMouse[1] = 0.5-mousePanel->getHeight()/2;        //correspond à la position verticale
	this->mousePanel->setPosition(this->posMouse[0], this->posMouse[1]);

	Ogre::OverlayContainer * mouseContainer = (Ogre::OverlayContainer*)OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIContainer");
	this->mouseOverlay->add2D(mouseContainer);
	mouseContainer->addChild(this->mousePanel);
	this->mouseOverlay->show(); 
}


void SelectionMouse::onMouseMoved(MouseMove_t &mouseMove)
{
	if(mouseMove.controlMouseId == Controls::NONE || mouseMove.controlMouseId == Controls::SELECT)
	{
		this->posMouse[0] = this->posMouse[0] + (mouseMove.vector[0]/this->winWidth);
		this->posMouse[1] = this->posMouse[1] + (mouseMove.vector[1]/this->winHeight);
		this->mousePanel->setPosition(posMouse[0], posMouse[1]);
        //permet de déplacer également la souris du menus CEGUI
        Menus::getSingletonPtr()->injectMouseMove (mouseMove.vector[0], mouseMove.vector[1]);
	}
	
	
	if(mouseMove.controlMouseId == Controls::SELECT)
	{
        if(this->selectedBriquetteOnMove != NULL)
        {
			Ogre::Vector3 plan = Ogre::Vector3(500.0, 1.0, 500.0);
			
			ObjBriquette * briquette = GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquetteOnMove);
			Ogre::SceneNode * nodeTest = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_TESTS);
			
			nodeTest->_setDerivedPosition(briquette->getSceneNode()->_getDerivedPosition());
			
			OgreBulletCollisions::CollisionShape * shapeTest = new OgreBulletCollisions::BoxCollisionShape(plan);
			OgreBulletDynamics::RigidBody * bodyTest = new OgreBulletDynamics::RigidBody("RigidBodyTest", ListenerCollision::getSingletonPtr()->getWorld(), COL_TEST_PLANE, TEST_PLANE_COLLIDES_WITH);
			//~ OgreBulletDynamics::RigidBody * bodyTest = new OgreBulletDynamics::RigidBody("RigidBodyTest", ListenerCollision::getSingletonPtr()->getWorld());
			bodyTest->setShape(nodeTest, shapeTest, 0.6, 0.6, 0.0, nodeTest->getPosition(), ObjBriquette::defaultOrientation);
					
			Ogre::Ray rayon;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallback = getResultUnderCursorUsingBullet(rayon);
			
			if (mCollisionClosestRayResultCallback->doesCollide())
			{
				OgreBulletDynamics::RigidBody * body = static_cast<OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallback->getCollidedObject());
				
				if(body->getName() == "RigidBodyTest")
				{
					this->selectedBriquetteOnMove->setPosition(
						mCollisionClosestRayResultCallback->getCollisionPoint()[0],
						0.0,
						mCollisionClosestRayResultCallback->getCollisionPoint()[2]
					);
				}
			}
			
			delete mCollisionClosestRayResultCallback;            
            delete shapeTest;
            delete bodyTest;
        }
    }
}

void SelectionMouse::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::SELECT:
            selectBriquette();
            break;
            
        default:
            break;
    }
}

void SelectionMouse::onKeyReleased(Controls::Controls key)
{
    switch(key)
    {
        case Controls::SELECT:
            unselectBriquette();
            break;
            
        default:
            break;
    }
}

void SelectionMouse::selectBriquette()
{
    Ogre::Ray rayon;
    OgreBulletDynamics::RigidBody * body = getBodyUnderCursorUsingBullet(rayon);
   
    if((body != NULL) && (!body->isStaticObject()))
    {
        this->selectedBriquetteOnMove = body;
        this->selectedBriquettePrevious = body;
        
        body->getBulletRigidBody()->forceActivationState(false);
        body->getBulletRigidBody()->clearForces();
        
        GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquetteOnMove)->getSceneNode()->setOrientation(ObjBriquette::defaultOrientation);
        //~ this->selectedBriquetteOnMove->getBulletRigidBody()->setOrientation(0.0);
        
        std::cout << "body: " << this->selectedBriquetteOnMove->getName() <<std::endl;
        std::cout << "orientation : " << *(this->selectedBriquetteOnMove->getBulletRigidBody()->getOrientation()) << std::endl;
    }
}


void SelectionMouse::unselectBriquette()
{
    if(this->selectedBriquetteOnMove != NULL)
    {
        //mettre a jour la bounding permet de la placer à la nouvelle position de la briquette
		ObjBriquette::updateBtBoundingBox(this->selectedBriquetteOnMove);
        
        
        this->selectedBriquetteOnMove = NULL;
        
        
        GestSnapShoot::getSingletonPtr()->addModification();
    }
}

OgreBulletDynamics::RigidBody * SelectionMouse::getBodyUnderCursorUsingBullet(Ogre::Ray &rayTo)
{
    Ogre::Camera * curCam = GestCamera::getSingletonPtr()->getCurrentCamera()->getCamera();
    
    Ogre::Real mouseScreenX = this->posMouse[0] + (this->mousePanel->getWidth() / 2.0);
    Ogre::Real mouseScreenY = this->posMouse[1] + (this->mousePanel->getHeight() / 2.0);
        
    rayTo = curCam->getCameraToViewportRay(mouseScreenX, mouseScreenY);
    
    OgreBulletDynamics::DynamicsWorld * world = ListenerCollision::getSingletonPtr()->getWorld();
    
    
    OgreBulletCollisions::CollisionClosestRayResultCallback *
    mCollisionClosestRayResultCallback = new
            OgreBulletCollisions::CollisionClosestRayResultCallback(rayTo, world, 5000);
            
    world->launchRay (*mCollisionClosestRayResultCallback);
    std::cout << "ray lauched" << std::endl;
    
    OgreBulletDynamics::RigidBody * bodyResult = NULL;
    
    if (mCollisionClosestRayResultCallback->doesCollide ())
    {
         bodyResult = static_cast<OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallback->getCollidedObject());
    }
    delete mCollisionClosestRayResultCallback;
    
    return bodyResult;
}

OgreBulletCollisions::CollisionClosestRayResultCallback * SelectionMouse::getResultUnderCursorUsingBullet(Ogre::Ray &rayTo)
{
    Ogre::Camera * curCam = GestCamera::getSingletonPtr()->getCurrentCamera()->getCamera();
    
    Ogre::Real mouseScreenX = this->posMouse[0] + (this->mousePanel->getWidth() / 2.0);
    Ogre::Real mouseScreenY = this->posMouse[1] + (this->mousePanel->getHeight() / 2.0);
        
    rayTo = curCam->getCameraToViewportRay(mouseScreenX, mouseScreenY);
    
    OgreBulletDynamics::DynamicsWorld * world = ListenerCollision::getSingletonPtr()->getWorld();
    
    
    OgreBulletCollisions::CollisionClosestRayResultCallback *
    mCollisionClosestRayResultCallback = new
            OgreBulletCollisions::CollisionClosestRayResultCallback(rayTo, world, 5000);
            
    world->launchRay (*mCollisionClosestRayResultCallback);
    
    return mCollisionClosestRayResultCallback;
}
