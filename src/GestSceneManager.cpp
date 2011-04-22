#include "GestSceneManager.h"

template<> GestSceneManager * ClassRootSingleton<GestSceneManager>::_instance = NULL;

void GestSceneManager::createSingleton()
{
	GestSceneManager::createSingleton(NULL);
}

void GestSceneManager::createSingleton(Ogre::Root * root)
{
	if (root == NULL)
	{
		std::cerr << "@GestSceneManager::createSingleton() : root is NULL" << std::endl;
	}
	else
	{
		new GestSceneManager(root);
	}
}

Ogre::SceneManager * GestSceneManager::getSceneManager()
{
	if(GestSceneManager::getSingletonPtr() != NULL)
		return GestSceneManager::getSingletonPtr()->sceneMgr;
		
	return NULL;
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
