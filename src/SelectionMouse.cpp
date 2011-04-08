#include "SelectionMouse.h"

using namespace Ogre;
using namespace OgreBulletCollisions;

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
    this->selectedBriquette=NULL;   
    PlayerControls::getSingletonPtr()->signalMouseMoved.add(&SelectionMouse::onMouseMoved, this);
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&SelectionMouse::onKeyPressed, this);
    PlayerControls::getSingletonPtr()->signalMouseMoved.add(&SelectionMouse::onMouseMoved, this);
}


void SelectionMouse::createOverlay(Ogre::RenderWindow * win)
{
    mouseOverlay = OverlayManager::getSingletonPtr()->create("GuiOverlay");
    mouseOverlay->setZOrder(600);
    mousePanel = (Ogre::OverlayElement *)
        OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIMouse");
    mousePanel->setMaterialName("TargetSights");

    TexturePtr mouseTex = TextureManager::getSingleton().load("target.png",
                            ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    this->winWidth= win->getWidth();
    this->winHeight= win->getHeight();
    mousePanel->setWidth (mouseTex->getWidth() / (float)this->winWidth); 
    mousePanel->setHeight (mouseTex->getHeight() / (float)this->winHeight);

    //la souris est centré initialement
    posMouse[0]=0.5;        //correspond à la position horizontale
    posMouse[1]=0.5;        //correspond à la position verticale
    mousePanel->setPosition(posMouse[0], posMouse[1]);

    Ogre::OverlayContainer      *mouseContainer = (Ogre::OverlayContainer*) 
        OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIContainer");
    mouseOverlay->add2D(mouseContainer);
    mouseContainer->addChild(mousePanel);
    mouseOverlay->show(); 
}


void SelectionMouse::onMouseMoved(MouseMove_t &mouseMove)
{
	if(mouseMove.controlMouseId == Controls::NONE || mouseMove.controlMouseId == Controls::SELECT)
	{
		posMouse[0] = posMouse[0] + (mouseMove.vector[0]/this->winWidth);
		posMouse[1] = posMouse[1] + (mouseMove.vector[1]/this->winHeight);
		mousePanel->setPosition(posMouse[0], posMouse[1]);
	}
    this->mouseMovedSelectedBriquette(mouseMove);
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

void SelectionMouse::selectBriquette()
{
    //this->selectedBriquette=NULL;
    Ogre::Ray rayon;
    OgreBulletDynamics::RigidBody * body = getBodyUnderCursorUsingBullet(rayon);
   
    //if(body == NULL)
    //    return;
    //std::cout<<"velocity : "<<body->getLinearVelocity()<<std::endl;
    //on va appliquer une force au corps pour l'élever un peu
    //body->applyImpulse(Ogre::Vector3(0.0, 0.0, 20.0), body->getCenterOfMassPosition());
    if((body!=NULL) && (! body->isStaticObject())){
        this->selectedBriquette= body;
        std::cout<<"body: "<<selectedBriquette->getName() <<std::endl;
    }
}

OgreBulletDynamics::RigidBody * SelectionMouse::getBodyUnderCursorUsingBullet(Ogre::Ray rayTo)
{
    Ogre::Camera * curCam=GestCamera::getSingletonPtr()->getCurrentCamera()->getCamera();
    rayTo = curCam->getCameraToViewportRay (posMouse[0]+(mousePanel->getHeight()/2.0),posMouse[1]+(mousePanel->getHeight()/2));
    OgreBulletDynamics::DynamicsWorld * world = ListenerCollision::getSingletonPtr()->getWorld();
    OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallback = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayTo, world, 5000);
    world->launchRay (*mCollisionClosestRayResultCallback);
    std::cout << "ray lauched" << std::endl;
    if (mCollisionClosestRayResultCallback->doesCollide ())
    {
        OgreBulletDynamics::RigidBody * body = static_cast<OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallback->getCollidedObject());
        
        //intersectionPoint = mCollisionClosestRayResultCallback->getCollisionPoint ();
        //std::cout << "Hit :" << body->getName() << std::endl;
        return body;
    }
    return NULL;
}

void SelectionMouse::mouseMovedSelectedBriquette (MouseMove_t &mouseMove){
	if(mouseMove.controlMouseId == Controls::SELECT){
        if(this->selectedBriquette != NULL){
            Ogre::Vector2 vecMouse= mouseMove.vector;
            //this->selectedBriquette->applyImpulse(Ogre::Vector3(0, vecMouse[1], vecMouse[0]),
            //                            this->selectedBriquette->getCenterOfMassPosition());
            this->selectedBriquette->setPosition(
                this->selectedBriquette->getSceneNode()->getPosition()[0]-mouseMove.vector[0],
                this->selectedBriquette->getSceneNode()->getPosition()[1],
                this->selectedBriquette->getSceneNode()->getPosition()[2]-mouseMove.vector[1]
            );
            this->updateBtBoundingBox(this->selectedBriquette);
        }
    }
}

void SelectionMouse::updateBtBoundingBox(OgreBulletDynamics::RigidBody * body){
    Ogre::Vector3 posOgre = body->getSceneNode()->_getDerivedPosition();
    Ogre::Quaternion dirOgre = body->getSceneNode()->_getDerivedOrientation();
    
    btVector3 posBt = OgreBtConverter::to(posOgre);
    btQuaternion dirBt = OgreBtConverter::to(dirOgre);
    

    //~ body->rigidBody->getBulletDynamicsWorld()->removeRigidBody(body->rigidBody->getBulletRigidBody());
    body->getBulletDynamicsWorld()->removeCollisionObject(body->getBulletRigidBody());
    body->getBulletObject()->getWorldTransform().setOrigin(posBt);
    body->getBulletObject()->getWorldTransform().setRotation(dirBt);
    body->getBulletDynamicsWorld()->addRigidBody(body->getBulletRigidBody());
}
