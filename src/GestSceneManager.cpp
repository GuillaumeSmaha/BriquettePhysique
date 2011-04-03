#include "GestSceneManager.h"

template<> GestSceneManager * ClassRootSingleton<GestSceneManager>::_instance = NULL;

void GestSceneManager::createSingleton()
{
	new GestSceneManager(NULL);
}

void GestSceneManager::createSingleton(Ogre::Root * root)
{
	if (root != NULL)
	{
		new GestSceneManager(root);
	}
	else
	{
		std::cerr << "@GestSceneManager::createSingleton() : root is NULL" << std::endl;
	}
}

Ogre::SceneManager * GestSceneManager::getSceneManager()
{
	return GestSceneManager::getSingletonPtr()->sceneMgr;
}

GestSceneManager::GestSceneManager(Ogre::Root * root) : ClassRootSingleton<GestSceneManager>()
{
	this->sceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
}

GestSceneManager::~GestSceneManager()
{
}

Ogre::Entity * GestSceneManager::createEntity(const Ogre::String &name, const Ogre::String meshName)
{
    return this->sceneMgr->createEntity(name, meshName);
}
