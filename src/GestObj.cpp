#include "GestObj.h"

template<> GestObj * ClassRootSingleton<GestObj>::_instance = NULL;


GestObj::GestObj() : ClassRootSingleton<GestObj>()
{
    this->table = NULL;
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
    ObjBriquette * briquettePtr = new ObjBriquette("Briquette"+Utils::toString(Utils::unique()));
    briquettePtr->setPosition(pos);
    
    //ajout dans la liste des briquettes
    this->lstBriquettes.push_back(briquettePtr);
    
    GestSnapShoot::getSingletonPtr()->addModification();
}


bool GestObj::existBriquette(ObjBriquette * briquette)
{
	std::vector<ObjBriquette *>::iterator it = this->lstBriquettes.begin();
	while (it != this->lstBriquettes.end())
    {
		if(*it == briquette)
			return true;
	}
	
	return false;
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


std::vector<ObjBriquette *> & GestObj::getListBriquettes()
{
	return this->lstBriquettes;
}


unsigned int GestObj::getNumberBriquettes()
{
	return this->lstBriquettes.size();
}

