#include "ObjTable.h"

ObjTable::ObjTable(Ogre::Real size, Ogre::Real depth)
{
    this->entTable = GestSceneManager::getSingletonPtr()->createEntity("Table"+Utils::toString(Utils::unique()), "Table.mesh");
    this->entTable->setMaterialName("Table");
    this->tableNode= GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode();
    this->tableNode->attachObject(entTable);

    this->tableNode->setScale(size, size, 1);
    std::cout << "table scale : " << tableNode->getScale() << std::endl;

	Ogre::Real center = size/2.0;
    this->tableNode->setPosition(center, center, depth);
    Ogre::Vector3 pos = this->tableNode->getPosition();
    Ogre::Quaternion dir = this->tableNode->getOrientation();

    this->shapeTable = new OgreBulletCollisions::BoxCollisionShape(tableNode->getScale());
    this->bodyTable= new OgreBulletDynamics::RigidBody("RigidBodyTable"+Utils::toString(Utils::unique()), ListenerCollision::getSingletonPtr()->getWorld());
    this->bodyTable->setStaticShape(this->tableNode, this->shapeTable, 0.6, 0.6, pos, dir);
    this->entTable->setCastShadows(true);
}

ObjTable::~ObjTable()
{
    delete this->tableNode;
    delete this->entTable;
    delete this->shapeTable;
    delete this->bodyTable;
}




