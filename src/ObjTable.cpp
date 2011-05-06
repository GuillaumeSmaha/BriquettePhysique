#include "ObjTable.h"

ObjTable::ObjTable(Ogre::Real size, Ogre::Real depth) : entTable(NULL), tableNode(NULL), shapeTable(NULL), bodyTable(NULL)
{
    this->entTable = GestSceneManager::getSingletonPtr()->createEntity("TableEntity"+Utils::toString(Utils::unique()), "Table.mesh");
    this->entTable->setMaterialName("Table");
    this->tableNode = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode("TableNode"+Utils::toString(Utils::unique()));
    this->tableNode->attachObject(this->entTable);

    this->tableNode->setScale(size, size, 1.0);

	Ogre::Real center = size/2.0;
    this->tableNode->setPosition(center, center, depth);
    
    this->createPhysicalObj();
}

ObjTable::~ObjTable()
{    
	this->removePhysicalObj();
		
	this->tableNode->detachObject(this->entTable);
	
	GestSceneManager::getSceneManager()->destroySceneNode(this->tableNode);
	GestSceneManager::getSceneManager()->destroyEntity(this->entTable);
}

void ObjTable::createPhysicalObj()
{
    Ogre::Vector3 pos = this->tableNode->getPosition();
    Ogre::Quaternion dir = this->tableNode->getOrientation();

    this->shapeTable = new OgreBulletCollisions::BoxCollisionShape(this->tableNode->getScale());
    this->bodyTable = new OgreBulletDynamics::RigidBody("RigidBodyTable"+Utils::toString(Utils::unique()), ListenerCollision::getSingletonPtr()->getWorld(), COL_TABLE, TABLE_COLLIDES_WITH);
    this->bodyTable->setStaticShape(this->tableNode, this->shapeTable, 0.0, 0.5, pos, dir);
    this->entTable->setCastShadows(true);
}

void ObjTable::removePhysicalObj()
{	
	if(this->bodyTable != NULL)
	{
		delete this->bodyTable;
		this->bodyTable = NULL;
	}
	
	if(this->shapeTable != NULL)
	{
		delete this->shapeTable;
		this->shapeTable = NULL;
	}
}
