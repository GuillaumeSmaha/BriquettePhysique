#include "SnapShoot.h"

SnapShoot::SnapShoot(ObjBriquette * object, Ogre::Vector3 diffPosition)
{
    this->objectCloned = false;
    this->object = object;
    this->diffPosition = diffPosition;
    this->diffOrientation = Ogre::Quaternion(0.0, 0.0, 0.0, 1.0);
}

SnapShoot::SnapShoot(ObjBriquette * object, Ogre::Quaternion diffOrientation)
{
    this->objectCloned = false;
    this->object = object;
    this->diffPosition = Ogre::Vector3(0.0, 0.0, 0.0);
    this->diffOrientation = diffOrientation;
}

SnapShoot::SnapShoot(ObjBriquette * object, Ogre::Vector3 diffPosition, Ogre::Quaternion diffOrientation)
{
    this->objectCloned = false;
    this->object = object;
    this->diffPosition = diffPosition;
    this->diffOrientation = diffOrientation;
}

SnapShoot::~SnapShoot()
{
	if(objectCloned == true)
		delete object;
}
