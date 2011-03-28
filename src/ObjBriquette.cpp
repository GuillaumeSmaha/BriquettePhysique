#include "ObjBriquette.h"

ObjBriquette::ObjBriquette(Ogre::String nom)
{
    this->nom=nom;
    this->entBriquette = GestSceneManager::getSingletonPtr()->createEntity(nom, "Briquette.mesh");
    this->entBriquette->setMaterialName("Briquette");
    //std::cout<<"briquette scale : "<<briquetteNode->getScale()<<std::endl;

}

ObjBriquette::~ObjBriquette()
{
}


void ObjBriquette::createPhysicalObj(){    

    this->briquetteNode->setScale(5, 0.5, 0.5);
    Ogre::Vector3 pos = this->briquetteNode->getPosition();
    Ogre::Quaternion dir = this->briquetteNode->getOrientation();

    this->shapeBriquette = new OgreBulletCollisions::BoxCollisionShape(briquetteNode->getScale());
    this->bodyBriquette= new OgreBulletDynamics::RigidBody("RigidBody"+this->nom, ListenerCollision::getSingletonPtr()->getWorld());
    this->bodyBriquette->setShape(this->briquetteNode, this->shapeBriquette, 0.6, 0.6, 1.0, pos, dir);
}


