#include "ObjBriquette.h"

ObjBriquette::ObjBriquette(Ogre::String nom, Ogre::Vector3 pos)
{
    this->nom = nom;
    this->entBriquette = GestSceneManager::getSingletonPtr()->createEntity(nom, "Briquette.mesh");
    this->entBriquette->setMaterialName("Briquette");
    //std::cout<<"briquette scale : "<<briquetteNode->getScale()<<std::endl;
    
    //positionnement dans le graphe de scene
    this->briquetteNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_BRIQUETTES)->createChildSceneNode();
    this->briquetteNode->attachObject(this->entBriquette);
    this->briquetteNode->setPosition(pos);
    
    //création de l'objet phyisque
    this->createPhysicalObj();

}

ObjBriquette::~ObjBriquette()
{
	if(this->briquetteNode != NULL)
	{
		this->briquetteNode->removeAndDestroyAllChildren();
		this->briquetteNode->getParentSceneNode()->removeAndDestroyChild(this->briquetteNode->getName());
	}
}

ObjBriquette::ObjBriquette(const ObjBriquette& briquette)
{
    nom = briquette.nom;
    entBriquette = GestSceneManager::getSingletonPtr()->createEntity(briquette.nom+"_"+Utils::toString(Utils::unique()), "Briquette.mesh");
    entBriquette->setMaterialName("Briquette");
    
    //positionnement dans le graphe de scene
    briquetteNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_BRIQUETTES)->createChildSceneNode();
    briquetteNode->attachObject(entBriquette);
    briquetteNode->setPosition(briquette.briquetteNode->getPosition());
    briquetteNode->setOrientation(briquette.briquetteNode->getOrientation());
    
    //création de l'objet phyisque
    this->createPhysicalObj();
}


void ObjBriquette::createPhysicalObj()
{
    this->briquetteNode->setScale(5, 0.5, 0.5);
    Ogre::Vector3 pos = this->briquetteNode->getPosition();
    Ogre::Quaternion dir = this->briquetteNode->getOrientation();

    this->shapeBriquette = new OgreBulletCollisions::BoxCollisionShape(briquetteNode->getScale());
    this->bodyBriquette= new OgreBulletDynamics::RigidBody("RigidBody"+this->nom, ListenerCollision::getSingletonPtr()->getWorld());
    this->bodyBriquette->setShape(this->briquetteNode, this->shapeBriquette, 0.6, 0.6, 10.0, pos, dir);
}



