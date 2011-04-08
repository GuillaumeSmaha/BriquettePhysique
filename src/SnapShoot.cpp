#include "SnapShoot.h"

SnapShoot::SnapShoot(Ogre::SceneNode * node, SnapShoot * lastSnapShoot)
{
    //~ this->objectCreate = false;
    //~ this->objectDelete = false;
    //~ this->node = node;
    //~ this->object = object;
    
    for(int i = 0 ; i < node->numChildren() ; i++)
    {
		//~ node->getChild(i)
		
	}    
}

SnapShoot::~SnapShoot()
{
	//~ if(this->objectCreate || this->objectDelete)
		//~ delete object;
}
