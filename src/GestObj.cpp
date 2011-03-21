#include "GestObj.h"

template<> GestObj * ClassRootSingleton<GestObj>::_instance = NULL;


GestObj::GestObj() : ClassRootSingleton<GestObj>()
{
    this->table = NULL;
}


GestObj::~GestObj()
{

}


void GestObj::setTable(ObjTable * table)
{
    if(this->table==NULL)
        this->table=table;
    else
       std::cerr << "@GestObj::setTable: object table already given" << std::endl;
}

void GestObj::addBriquette(ObjBriquette* briquette)
{
    this->lstBriquettes.push_back(briquette);
}
