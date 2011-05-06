#include "SnapShoot.h"

SnapShoot::SnapShoot()
{
	bool state = ListenerCollision::getSingletonPtr()->getPhysicEngineState();
	
	ListenerCollision::getSingletonPtr()->physicEngineMutexLock(this);
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(false, this);
	
	
	std::vector<ObjBriquette *>::iterator it;
	for(it = GestObj::getSingletonPtr()->getListBriquettes().begin() ; it < GestObj::getSingletonPtr()->getListBriquettes().end() ; it ++)
	{			
		if((*it)->isDrawing())
		{
			SnapShootData * data = new SnapShootData;
			
			data->object = *it;
			data->position = (*it)->getSceneNode()->getPosition();
			data->orientation = (*it)->getSceneNode()->getOrientation();
			
			this->lstPosition.push_back(data);
		}
	}
	
	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(state, this);
	ListenerCollision::getSingletonPtr()->physicEngineMutexUnLock(this);
}

SnapShoot::~SnapShoot()
{
	std:: vector<SnapShootData *>::iterator it = this->lstPosition.begin();
	while (it != this->lstPosition.end())
    {
		delete *it;
		it = this->lstPosition.erase(it);
	}
}


SnapShootData * SnapShoot::findData(ObjBriquette * briquette)
{
	std::vector<SnapShootData *>::iterator it = this->lstPosition.begin();
	while (it != this->lstPosition.end())
    {
		if((*it)->object == briquette)
			return *it;
			
		it++;
	}
	
	return NULL;
}


SnapShootData * SnapShoot::findData(SnapShootData * data)
{
	std::vector<SnapShootData *>::iterator it = this->lstPosition.begin();
	while (it != this->lstPosition.end())
    {
		if(*it== data)
			return *it;
			
		it++;
	}
	
	return NULL;
}


bool SnapShoot::existData(ObjBriquette * briquette)
{
	std::vector<SnapShootData *>::iterator it = this->lstPosition.begin();
	while (it != this->lstPosition.end())
    {
		if((*it)->object == briquette)
			return true;
	}
	
	return false;
}

std::vector<SnapShootData *> & SnapShoot::getListData()
{
	return this->lstPosition;
}

unsigned int SnapShoot::getNumberData()
{
	return this->lstPosition.size();
}
