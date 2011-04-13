#include "GestSnapShoot.h"

template<> GestSnapShoot * ClassRootSingleton<GestSnapShoot>::_instance = NULL;


GestSnapShoot::GestSnapShoot() : ClassRootSingleton<GestSnapShoot>()
{
    this->currentSnapShoot = 0;
    
    //add an empty SnapShoot
	SnapShoot * snapShoot = new SnapShoot();
    
	this->lstSnapShoot.push_back(snapShoot);
    
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&GestSnapShoot::onKeyPressed, this);
}


GestSnapShoot::~GestSnapShoot()
{
	PlayerControls::getSingletonPtr()->signalKeyPressed.remove(&GestSnapShoot::onKeyPressed, this);
}

void GestSnapShoot::addModification()
{
	if(this->currentSnapShoot != (this->lstSnapShoot.size()-1))
	{
		this->removeLastModification(this->lstSnapShoot.size()-this->currentSnapShoot-1);
	}
	
	SnapShoot * snapShoot = new SnapShoot();
		
	this->lstSnapShoot.push_back(snapShoot);
	this->currentSnapShoot++;
}


unsigned int GestSnapShoot::getCurrentRevision()
{
	return this->currentSnapShoot;
}


unsigned int GestSnapShoot::getNumberRevision()
{
	return this->lstSnapShoot.size() - 1;
}


void GestSnapShoot::removeFirstModification(unsigned int numberModification)
{
	for(unsigned int i = 0 ; i < numberModification ; i++)
	{
		SnapShoot * tmp = this->lstSnapShoot.front();
		this->lstSnapShoot.pop_front();
		delete tmp;
	}
}

void GestSnapShoot::removeLastModification(unsigned int numberModification)
{
	for(unsigned int i = 0 ; i < numberModification ; i++)
	{
		SnapShoot * tmp = this->lstSnapShoot.back();
		this->lstSnapShoot.pop_back();
		delete tmp;
	}
}

void GestSnapShoot::undo(unsigned int numberModification)
{
	ListenerCollision::getSingletonPtr()->physicEngineMutexLock(this);	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(false, this);
	
	this->_applyRevision(this->currentSnapShoot-numberModification);
	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(true, this);	
	ListenerCollision::getSingletonPtr()->physicEngineMutexUnLock(this);
}

void GestSnapShoot::undoAll()
{
	ListenerCollision::getSingletonPtr()->physicEngineMutexLock(this);	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(false, this);
	
	this->_applyRevision(0);
	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(true, this);	
	ListenerCollision::getSingletonPtr()->physicEngineMutexUnLock(this);
}

void GestSnapShoot::redo(unsigned int numberModification)
{
	ListenerCollision::getSingletonPtr()->physicEngineMutexLock(this);	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(false, this);
	
	this->_applyRevision(this->currentSnapShoot+numberModification);
	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(true, this);	
	ListenerCollision::getSingletonPtr()->physicEngineMutexUnLock(this);
}

void GestSnapShoot::redoAll()
{
	ListenerCollision::getSingletonPtr()->physicEngineMutexLock(this);	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(false, this);
	
	this->_applyRevision(this->lstSnapShoot.size()-1);
	
	ListenerCollision::getSingletonPtr()->setPhysicEngineState(true, this);	
	ListenerCollision::getSingletonPtr()->physicEngineMutexUnLock(this);
}

void GestSnapShoot::_applyRevision(int iVersion)
{
	if(iVersion < 0)
	{
		iVersion = 0;
	}
	else if(iVersion >= (this->lstSnapShoot.size()-1))
	{
		iVersion = this->lstSnapShoot.size()-1;
	}
	
	if(this->currentSnapShoot == static_cast<unsigned int>(iVersion))
	{
		return;
	}
	
	this->currentSnapShoot = static_cast<unsigned int>(iVersion);
	
	std::cerr << "Apply the revision " << this->currentSnapShoot << std::endl;
	
	//Hide all briquettte
	std::vector<ObjBriquette *>::iterator itB = GestObj::getSingletonPtr()->getListBriquettes().begin();
	while (itB !=GestObj::getSingletonPtr()->getListBriquettes().end())
	{
		ObjBriquette * briquette = *itB;
		
		briquette->hide();
				
		itB++;
	}
	
	//Show only the good briquettte
	SnapShoot * snapShoot = this->lstSnapShoot.at(this->currentSnapShoot);
	
	std::vector<SnapShootData *>::iterator itS = snapShoot->getListData().begin();
	while (itS != snapShoot->getListData().end())
	{
		SnapShootData * data = *itS;
		ObjBriquette * briquette = data->object;
		
		briquette->draw();
			
		briquette->setPosition(data->position);
		briquette->setOrientation(data->orientation);
				
		itS++;
	}
}


void GestSnapShoot::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::UNDO:
            this->undo();
            break;
            
        case Controls::REDO:
            this->redo();
            break;
            
        default:
            break;
    }
}
