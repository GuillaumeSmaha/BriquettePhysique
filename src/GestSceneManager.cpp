#include "GestSceneManager.h"


GestSceneManager * GestSceneManager::_instance = NULL;


void GestSceneManager::createSingleton(Ogre::Root * root)
{
	if (_instance == NULL)
	{
		_instance = new GestSceneManager(root);
	}
}

GestSceneManager * GestSceneManager::getSingletonPtr()
{
	if (_instance == NULL)
	{
		std::cerr << "@GestSceneManager::getSingletonPtr() : _instance is NULL" << std::endl;
		return NULL;
	}
	return _instance;
}

GestSceneManager & GestSceneManager::getSingleton()
{
	if (_instance == NULL)
	{
		std::cerr << "@GestSceneManager::getSingleton() : _instance is NULL" << std::endl;
	}
	return *_instance;
}

void GestSceneManager::destroySingleton()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}

Ogre::SceneManager * GestSceneManager::getSceneManager()
{
	return GestSceneManager::getSingletonPtr()->sceneMgr;
}

GestSceneManager::GestSceneManager(Ogre::Root * root)
{
	if (_instance == NULL)
	{
		this->sceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
		_instance = this;
	}
}

GestSceneManager::~GestSceneManager()
{
}


Ogre::Entity * GestSceneManager::createEntity(const Ogre::String &name, const Ogre::String meshName)
{
    return this->sceneMgr->createEntity(name, meshName);
}
