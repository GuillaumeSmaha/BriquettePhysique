#include "ObjBriquette.h"

ObjBriquette::ObjBriquette()
{
    this->entBriquette = GestSceneManager::getSingletonPtr()->createEntity("Briquette", "Briquette.mesh");
    this->entBriquette->setMaterialName("Briquette");
    //this->briquetteNode->setScale(1000, 1000, 1);
    //std::cout<<"briquette scale : "<<briquetteNode->getScale()<<std::endl;

}

ObjBriquette::~ObjBriquette()
{
}


void ObjBriquette::createPhysicalObj(){    

    Ogre::Vector3 pos = this->briquetteNode->getPosition();
    Ogre::Quaternion dir = this->briquetteNode->getOrientation();

    this->shapeBriquette = new OgreBulletCollisions::BoxCollisionShape(briquetteNode->getScale());
    this->bodyBriquette= new OgreBulletDynamics::RigidBody("RigidBodyBriquette", ListenerCollision::getSingletonPtr()->getWorld());
    this->bodyBriquette->setShape(this->briquetteNode, this->shapeBriquette, 0.6, 0.6, 1.0, pos, dir);
}



