#include "GestSnapShoot.h"

template<> GestSnapShoot * ClassRootSingleton<GestSnapShoot>::_instance = NULL;


GestSnapShoot::GestSnapShoot() : ClassRootSingleton<GestSnapShoot>()
{
    this->currentSnapShoot = -1;
}


GestSnapShoot::~GestSnapShoot()
{
}

void GestSnapShoot::addModification()
{
	SnapShoot * snapShoot;
	if(this->lstSnapShoot.size() == 0)
	{
		snapShoot = new SnapShoot(NULL);
		this->currentSnapShoot = 0;
	}
	else
	{
		if(this->currentSnapShoot != (this->lstSnapShoot.size()-1))
		{
			this->removeLastModification(this->lstSnapShoot.size()-this->currentSnapShoot-1);
		}
		snapShoot = new SnapShoot(this->lstSnapShoot.back());
		this->currentSnapShoot++;
	}
		
	this->lstSnapShoot.push_back(snapShoot);
	
	std::cerr << "Number SnapShoot = " << this->lstSnapShoot.size() << std::endl;
}

void GestSnapShoot::removeFirstModification(int numberModification)
{
	for(int i = 0 ; i < numberModification ; i++)
	{
		SnapShoot * tmp = this->lstSnapShoot.front();
		this->lstSnapShoot.pop_front();
		delete tmp;
	}
}

void GestSnapShoot::removeLastModification(int numberModification)
{
	for(int i = 0 ; i < numberModification ; i++)
	{
		SnapShoot * tmp = this->lstSnapShoot.back();
		this->lstSnapShoot.pop_back();
		delete tmp;
	}
}

void GestSnapShoot::undo(int numberModification)
{
}

void GestSnapShoot::undoAll()
{
}

void GestSnapShoot::redo(int numberModification)
{
}

void GestSnapShoot::redoAll()
{
}
