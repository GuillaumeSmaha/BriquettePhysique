#include "GestObj.h"

template<> GestObj * ClassRootSingleton<GestObj>::_instance = NULL;


GestObj::GestObj() : ClassRootSingleton<GestObj>()
{
    this->table = NULL;
    this->groupBriquetteNode = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_BRIQUETTES);
}


GestObj::~GestObj()
{
    //désalloue la table et l'ensemble des briquettes
	if(this->tableBackground != NULL)
		delete this->tableBackground;
		
	if(this->table != NULL)
		delete this->table;
		
    std::vector<ObjBriquette *>::iterator it;
    for(it = this->lstBriquettes.begin() ; it <this->lstBriquettes.end() ; it ++)
        delete *it ;
}

void GestObj::addBriquette(const Ogre::Vector3 &pos)
{
    //crée la briquette
    ObjBriquette * briquette = new ObjBriquette("Briquette"+Utils::toString(Utils::unique()));

    //positionnement dans le graphe de scene
    briquette->setSceneNode(this->getGroupBriquetteNode()->createChildSceneNode());
    briquette->getSceneNode()->attachObject(briquette->getEntity());
    briquette->getSceneNode()->setPosition(pos);
    //création de l'objet phyisque
    briquette->createPhysicalObj();

    //ajout dans la liste des briquettes
    this->lstBriquettes.push_back(briquette);
}


void GestObj::setTableBackground(ObjTable * tableBackground)
{
    if(this->tableBackground == NULL)
        this->tableBackground = tableBackground;
    else
       std::cerr << "@GestObj::setTableBackground: object table already given" << std::endl;
}


void GestObj::setTable(ObjTable * table)
{
    if(this->table == NULL)
        this->table = table;
    else
       std::cerr << "@GestObj::setTable: object table already given" << std::endl;
}
