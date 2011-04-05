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




SelectionMouse::SelectionMouse(Ogre::RenderWindow * win): ClassRootSingleton<SelectionMouse>()
{
    createOverlay(win);
    PlayerControls::getSingletonPtr()->signalMouseSelectMoved.add(&SelectionMouse::onMouseMoved, this);
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&SelectionMouse::onKeyPressed, this);
}


void SelectionMouse::createOverlay(Ogre::RenderWindow * win)
{
    mouseOverlay = OverlayManager::getSingletonPtr()->create("GuiOverlay");
    mouseOverlay->setZOrder(600);
    mousePanel = (Ogre::OverlayElement *)
        OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIMouse");
    mousePanel->setMaterialName("OgreBulletDemos/TargetSights");

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


void SelectionMouse::onMouseMoved(Ogre::Vector3 mouseVec)
{   
    posMouse[0]=posMouse[0] + (mouseVec[0]/this->winWidth);
    posMouse[1]=posMouse[1] + (mouseVec[1]/this->winHeight);
    mousePanel->setPosition (posMouse[0],posMouse[1] );
}

void SelectionMouse:: onKeyPressed(Controls::Controls key){
    switch(key)
    {
        case Controls::SELECT:
            catchBriquette();
            break;
        default:
            break;
    }
}

void SelectionMouse::catchBriquette(){
    Ogre::Ray rayon;
    OgreBulletDynamics::RigidBody * body = 
        getBodyUnderCursorUsingBullet(rayon);
    if (body==NULL)
        return;
    //on va appliquer une force au corps pour l'élever un peu
    body->applyImpulse(Ogre::Vector3(0,0,20), body->getCenterOfMassPosition());
}

OgreBulletDynamics::RigidBody * SelectionMouse::getBodyUnderCursorUsingBullet(Ogre::Ray rayTo){
    Ogre::Camera * curCam=GestCamera::getSingletonPtr()->getCurrentCamera()->getCamera();
    rayTo = curCam->getCameraToViewportRay (posMouse[0]+(mousePanel->getHeight()/2),posMouse[1]+(mousePanel->getHeight()/2));
    OgreBulletDynamics::DynamicsWorld * world = ListenerCollision::getSingletonPtr()->getWorld();
    OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallback = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayTo, world, 5000);
    world->launchRay (*mCollisionClosestRayResultCallback);
    std::cout<<"ray lauched"<<std::endl;
    if (mCollisionClosestRayResultCallback->doesCollide ())
    {
        OgreBulletDynamics::RigidBody * body = static_cast <OgreBulletDynamics::RigidBody *> 
            (mCollisionClosestRayResultCallback->getCollidedObject());
        
        //intersectionPoint = mCollisionClosestRayResultCallback->getCollisionPoint ();
        std::cout<<"Hit :"<<body->getName()<<std::endl;
        return body;
    }
    return NULL;
}
