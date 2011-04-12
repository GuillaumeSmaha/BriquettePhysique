#include "SnapShoot.h"

SnapShoot::SnapShoot(SnapShoot * lastSnapShoot)
{	
	ListenerCollision::getSingletonPtr()->physicEngineMutexLock(this);
	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(false, this);
	
    if(lastSnapShoot == NULL || lastSnapShoot->getNumberData() == GestObj::getSingletonPtr()->getNumberBriquettes())
    {
		std::vector<ObjBriquette *>::iterator it;
		for(it = GestObj::getSingletonPtr()->getListBriquettes().begin() ; it < GestObj::getSingletonPtr()->getListBriquettes().end() ; it ++)
		{
			std::cerr << "Briquette : " << *it << std::endl;
			
			SnapShootData * data = new SnapShootData;
			data->object = *it;
			if(lastSnapShoot == NULL)
				data->objectCreate = true;
			else
				data->objectCreate = false;
			data->objectDelete = false;
			data->position = (*it)->getSceneNode()->getPosition();
			data->orientation = (*it)->getSceneNode()->getOrientation();
			
			this->lstPosition.push_back(data);
		}
	}
	else if(lastSnapShoot->getNumberData() < GestObj::getSingletonPtr()->getNumberBriquettes()) //Si on a ajouté une donnée
	{
		std::vector<ObjBriquette *>::iterator it;
		for(it = GestObj::getSingletonPtr()->getListBriquettes().begin() ; it < GestObj::getSingletonPtr()->getListBriquettes().end() ; it ++)
		{
			SnapShootData * data = new SnapShootData;
			data->object = *it;
			
			if(lastSnapShoot->existData(*it))
				data->objectCreate = false;
			else
				data->objectCreate = true;

			data->objectDelete = false;
			data->position = (*it)->getSceneNode()->getPosition();
			data->orientation = (*it)->getSceneNode()->getOrientation();
			
			this->lstPosition.push_back(data);
		}
	}
	else //Si on a supprimé une donnée
	{
		std:: vector<SnapShootData *>::iterator it;
		for(it = this->lstPosition.begin() ; it < this->lstPosition.end() ; it ++)
		{
			SnapShootData * data = new SnapShootData;

			if(GestObj::getSingletonPtr()->existBriquette((*it)->object))
			{
				data->objectDelete = false;
				data->object = (*it)->object;
			}
			else
			{
				data->objectDelete = true;
				//~ data->object = new ObjBriquette(*(*it));
				data->object = (*it)->object;
			}			
			
			data->objectCreate = false;
			data->position = ((*it)->object)->getSceneNode()->getPosition();
			data->orientation = ((*it)->object)->getSceneNode()->getOrientation();
			
			this->lstPosition.push_back(data);
		}
	}
	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(true, this);
	
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

int SnapShoot::getNumberData()
{
	return this->lstPosition.size();
}
