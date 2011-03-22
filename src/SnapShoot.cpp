#include "SnapShoot.h"

SnapShoot::SnapShoot(Ogre::SceneNode * node, ObjBriquette * object, Ogre::Vector3 diffPosition)
{
    this->objectCreate = false;
    this->objectDelete = false;
    this->node = node;
    this->object = object;
    this->diffPosition = diffPosition;
    this->diffOrientation = Ogre::Quaternion(0.0, 0.0, 0.0, 1.0);
}

SnapShoot::SnapShoot(Ogre::SceneNode * node, ObjBriquette * object, Ogre::Quaternion diffOrientation)
{
    this->objectCreate = false;
    this->objectDelete = false;
    this->node = node;
    this->object = object;
    this->diffPosition = Ogre::Vector3(0.0, 0.0, 0.0);
    this->diffOrientation = diffOrientation;
}

SnapShoot::SnapShoot(Ogre::SceneNode * node, ObjBriquette * object, Ogre::Vector3 diffPosition, Ogre::Quaternion diffOrientation)
{
    this->objectCreate = false;
    this->objectDelete = false;
    this->node = node;
    this->object = object;
    this->diffPosition = diffPosition;
    this->diffOrientation = diffOrientation;
}

SnapShoot::~SnapShoot()
{
	if(this->objectCreate || this->objectDelete)
		delete object;
}
