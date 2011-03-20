#include "GestObj.h"


GestObj * GestObj::_instance = NULL;


void GestObj::createSingleton()
{
	if (_instance == NULL)
	{
		_instance = new GestObj();
	}
}

GestObj * GestObj::getSingletonPtr()
{
	if (_instance == NULL)
	{
		_instance = new GestObj();
	}
	return _instance;
}

GestObj & GestObj::getSingleton()
{
	if (_instance == NULL)
	{
		_instance = new GestObj();
	}
	return *_instance;
}

void GestObj::destroySingleton()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}

GestObj::GestObj(){
    this->table=NULL;
}
GestObj::~GestObj(){

}


void GestObj::setTable(ObjTable * table)
{
    if(this->table==NULL)
        this->table=table;
    else
       std::cerr << "@GestObj::setTable: object table already given" << std::endl;
}

void GestObj::addBriquette(ObjBriquette* briquette){
    this->lstBriquettes.push_back(briquette);
}
