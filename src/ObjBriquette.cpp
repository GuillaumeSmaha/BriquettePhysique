#include "ObjBriquette.h"

//A retenir : rigidBody->getBulletRigidBody()->clearForces()
//A retenir : rigidBody->getBulletRigidBody()->forceActivationState(false)
//A retenir : rigidBody->getBulletRigidBody()->activate(false)


Ogre::Quaternion ObjBriquette::defaultOrientation = Ogre::Quaternion(0.0, 0.0, 0.0, 1.0);


void ObjBriquette::updateBtBoundingBox(OgreBulletDynamics::RigidBody * rigidBody)
{
    Ogre::Vector3 posOgre = rigidBody->getSceneNode()->_getDerivedPosition();
    Ogre::Quaternion dirOgre = rigidBody->getSceneNode()->_getDerivedOrientation();
    
    btVector3 posBt = OgreBulletCollisions::OgreBtConverter::to(posOgre);
    btQuaternion dirBt = OgreBulletCollisions::OgreBtConverter::to(dirOgre);
    

    rigidBody->getBulletDynamicsWorld()->removeCollisionObject(rigidBody->getBulletRigidBody());
    rigidBody->getBulletObject()->getWorldTransform().setOrigin(posBt);
    rigidBody->getBulletObject()->getWorldTransform().setRotation(dirBt);
    rigidBody->getBulletDynamicsWorld()->addRigidBody(rigidBody->getBulletRigidBody());
    rigidBody->enableActiveState();
    
        
	rigidBody->getBulletRigidBody()->activate(true);
}



ObjBriquette::ObjBriquette(Ogre::String nom)
{
    this->nom = nom;
    this->_isDrawing = true;
    this->entBriquette = GestSceneManager::getSingletonPtr()->createEntity(nom, "Briquette.mesh");
    this->entBriquette->setMaterialName("Briquette");
    //std::cout<<"briquette scale : "<<briquetteNode->getScale()<<std::endl;
    
    //positionnement dans le graphe de scene
    this->briquetteNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_BRIQUETTES)->createChildSceneNode("Node_"+nom);
    this->briquetteNode->attachObject(this->entBriquette);
        
    //création de l'objet phyisque
    this->createPhysicalObj();
}

ObjBriquette::ObjBriquette(const ObjBriquette& briquette)
{
    nom = briquette.nom;
    this->_isDrawing = briquette._isDrawing;
    entBriquette = GestSceneManager::getSingletonPtr()->createEntity(briquette.nom+"_"+Utils::toString(Utils::unique()), "Briquette.mesh");
    entBriquette->setMaterialName("Briquette");
    
    //positionnement dans le graphe de scene
    briquetteNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_BRIQUETTES)->createChildSceneNode("Node_"+briquette.nom);
    briquetteNode->attachObject(entBriquette);
    briquetteNode->setPosition(briquette.briquetteNode->getPosition());
    briquetteNode->setOrientation(briquette.briquetteNode->getOrientation());
    
    //création de l'objet phyisque
    this->createPhysicalObj();
}

ObjBriquette::~ObjBriquette()
{	
	this->removePhysicalObj();
	
	if(this->briquetteNode != NULL)
	{
		this->briquetteNode->removeAndDestroyAllChildren();
		this->briquetteNode->getParentSceneNode()->removeAndDestroyChild(this->briquetteNode->getName());
	}
}

void ObjBriquette::setPosition(Ogre::Vector3 pos)
{
    this->briquetteNode->setPosition(pos);
    ObjBriquette::updateBtBoundingBox(this->bodyBriquette);
}

void ObjBriquette::setOrientation(Ogre::Quaternion orientation)
{
    this->briquetteNode->setOrientation(orientation);
    ObjBriquette::updateBtBoundingBox(this->bodyBriquette);
}

void ObjBriquette::createPhysicalObj()
{
    this->briquetteNode->setScale(5, 3.0, 0.5);
    Ogre::Vector3 pos = this->briquetteNode->getPosition();
    //~ Ogre::Quaternion dir = this->briquetteNode->getOrientation();
    Ogre::Quaternion dir = ObjBriquette::defaultOrientation;

    this->shapeBriquette = new OgreBulletCollisions::BoxCollisionShape(briquetteNode->getScale());
    this->bodyBriquette = new OgreBulletDynamics::RigidBody("RigidBody"+this->nom, ListenerCollision::getSingletonPtr()->getWorld(), COL_BRIQUETTE, BRIQUETTE_COLLIDES_WITH);
    //~ this->bodyBriquette = new OgreBulletDynamics::RigidBody("RigidBody"+this->nom, ListenerCollision::getSingletonPtr()->getWorld());
    this->bodyBriquette->setShape(this->briquetteNode, this->shapeBriquette, 0.6, 0.6, 10.0, pos, dir);
    
    
	std::pair<OgreBulletDynamics::RigidBody *, ObjBriquette *> ret = std::pair<OgreBulletDynamics::RigidBody *, ObjBriquette *>(this->bodyBriquette, this);
    
	GestObj::getSingletonPtr()->getListRigidBodyToBriquette().insert(ret);
}

void ObjBriquette::removePhysicalObj()
{	
	GestObj::getSingletonPtr()->getListRigidBodyToBriquette().erase(this->bodyBriquette);
	
	if(this->bodyBriquette != NULL)
	{
		delete this->bodyBriquette;
		this->bodyBriquette = NULL;
	}
	
	if(this->shapeBriquette != NULL)
	{
		delete this->shapeBriquette;
		this->shapeBriquette = NULL;
	}
}



void ObjBriquette::hide()
{
	if(this->_isDrawing)
	{
		//~ this->briquetteNode->detachObject(this->entBriquette);
		this->entBriquette->setVisible(false);
		this->_isDrawing = false;
		this->bodyBriquette->getBulletRigidBody()->activate(false);
		this->removePhysicalObj();
	}
}


void ObjBriquette::draw()
{
	if(!this->_isDrawing)
	{
		//~ this->briquetteNode->attachObject(this->entBriquette);
		this->_isDrawing = true;
		this->entBriquette->setVisible(true);
		this->createPhysicalObj();
		ObjBriquette::updateBtBoundingBox(this->bodyBriquette);
	}
}


bool ObjBriquette::isDrawing()
{
    return this->_isDrawing;
}
