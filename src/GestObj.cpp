#include "GestObj.h"

template<> GestObj * ClassRootSingleton<GestObj>::_instance = NULL;


GestObj::GestObj() : ClassRootSingleton<GestObj>()
{
    this->table = NULL;
    this->groupBriquetteNode= GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode();
}


GestObj::~GestObj()
{
    //désalloue la table et l'ensemble des briquettes
    delete(this->table);
    std::vector<ObjBriquette *>::iterator it;
    for(it=this->lstBriquettes.begin(); it <this->lstBriquettes.end(); it ++)
        delete(*it);
}


void GestObj::setTable(ObjTable * table)
{
    if(this->table==NULL)
        this->table=table;
    else
       std::cerr << "@GestObj::setTable: object table already given" << std::endl;
}

void GestObj::addBriquette(const Ogre::Vector3 &pos)
{
    //crée la briquette
    ObjBriquette * briquette= new ObjBriquette("Briquette"+Utils::toString(Utils::unique()));

    //positionnement dans le graphe de scene
    briquette->setSceneNode(this->getGroupBriquetteNode()->createChildSceneNode());
    briquette->getSceneNode()->attachObject(briquette->getEntity());
    briquette->getSceneNode()->setPosition(pos);
    //création de l'objet phyisque
    briquette->createPhysicalObj();

    //ajout dans la liste des briquettes
    this->lstBriquettes.push_back(briquette);
}
