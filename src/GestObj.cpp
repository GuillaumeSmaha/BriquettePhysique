#include "GestObj.h"

template<> GestObj * ClassRootSingleton<GestObj>::_instance = NULL;


GestObj::GestObj() : ClassRootSingleton<GestObj>()
{
    this->table = NULL;
    this->groupBriquetteNode= GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode();
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

void GestObj::addBriquette()
{
    //crée la briquette
    ObjBriquette * briquette= new ObjBriquette();

    //positionnement dans le graphe de scene
    briquette->setSceneNode(this->getGroupBriquetteNode()->createChildSceneNode());
    briquette->getSceneNode()->attachObject(briquette->getEntity());
    
    //création de l'objet phyisque
    briquette->createPhysicalObj();

    //ajout dans la liste des briquettes
    this->lstBriquettes.push_back(briquette);
}
