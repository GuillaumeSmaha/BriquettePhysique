#include "ObjTable.h"

ObjTable::ObjTable()
{
    this->entTable = GestSceneManager::getSingletonPtr()->createEntity("Table", "Table.mesh");
    this->entTable->setMaterialName("Table");
    this->tableNode= GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode();
    this->tableNode->attachObject(entTable);

    this->tableNode->setScale(100, 100, 1);
    std::cout<<"table scale : "<<tableNode->getScale()<<std::endl;

    this->tableNode->setPosition(0,0,0);
    Ogre::Vector3 pos = this->tableNode->getPosition();
    Ogre::Quaternion dir = this->tableNode->getOrientation();

    this->shapeTable = new OgreBulletCollisions::BoxCollisionShape(tableNode->getScale());
    this->bodyTable= new OgreBulletDynamics::RigidBody("RigidBodyTable", ListenerCollision::getSingletonPtr()->getWorld());
    this->bodyTable->setShape(this->tableNode, this->shapeTable, 0.6, 0.6, 1.0, pos, dir);
    this->entTable->setCastShadows(true);
}

ObjTable::~ObjTable()
{
    delete(this->tableNode);
    delete(this->entTable);
    delete(this->shapeTable);
    delete(this->bodyTable);

}




