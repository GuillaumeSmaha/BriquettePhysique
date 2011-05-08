#include "GestObj.h"

template<> GestObj * ClassRootSingleton<GestObj>::_instance = NULL;


GestObj::GestObj() : ClassRootSingleton<GestObj>()
{
    this->tableBackground = NULL;
    this->table = NULL;
}


GestObj::~GestObj()
{
    //désalloue la table et l'ensemble des briquettes
	if(this->tableBackground != NULL)
	{
		this->tableBackground = NULL;
		delete this->tableBackground;
	}
		
	if(this->table != NULL)
	{
		this->table = NULL;
		delete this->table;
	}
		
    std::vector<ObjBriquette *>::iterator it;
    for(it = this->lstBriquettes.begin() ; it <this->lstBriquettes.end() ; it ++)
        delete *it;
}


int GestObj::getCountBriquetteDrawed()
{
	int countRes = 0;
	std::vector<ObjBriquette *>::iterator it;
		
    for(it = this->lstBriquettes.begin() ; it <this->lstBriquettes.end() ; it ++)
        if((*it)->isDrawing())
			countRes++;
			
	return countRes;
}


void GestObj::addBriquette(const Ogre::Vector3 &pos)
{
    //crée la briquette
    ObjBriquette * briquettePtr = new ObjBriquette("Briquette"+Utils::toString(Utils::unique()));
    briquettePtr->setPosition(pos);
    
    //ajout dans la liste des briquettes
    this->lstBriquettes.push_back(briquettePtr);
    
    GestGame::getSingletonPtr()->addModification();
}


bool GestObj::existBriquette(ObjBriquette * briquette)
{
	std::vector<ObjBriquette *>::iterator it = this->lstBriquettes.begin();
	while (it != this->lstBriquettes.end())
    {
		if(*it == briquette)
			return true;
			
		it++;
	}
	
	return false;
}


void GestObj::removeBriquette(ObjBriquette * briquette)
{
	if(this->existBriquette(briquette))
	{
		std::vector<ObjBriquette *>::iterator it = this->lstBriquettes.begin();
		while (it != this->lstBriquettes.end())
		{
			if(*it == briquette)
			{
				this->lstBriquettes.erase(it);
				delete briquette;
				break;
			}
			
			it++;
		}
	}
}


void GestObj::updateAllForces()
{
    std::vector<ObjBriquette *> lstBriquettes = this->getListBriquettes();
    std::vector<ObjBriquette *>::iterator it;
    for(it = lstBriquettes.begin() ; it < lstBriquettes.end() ; it ++)
    {
		if((*it)->isDrawing())
		{
			ObjBriquette::updateBtBoundingBox((*it)->getRigidBody());
		}
    }
}


void GestObj::clearAllForces()
{
    std::vector<ObjBriquette *> lstBriquettes = this->getListBriquettes();
    std::vector<ObjBriquette *>::iterator it;
    for(it = lstBriquettes.begin() ; it < lstBriquettes.end() ; it ++)
    {
		if((*it)->isDrawing())
		{
			(*it)->getRigidBody()->getBulletRigidBody()->forceActivationState(false);
			(*it)->getRigidBody()->getBulletRigidBody()->clearForces();
		}
    }
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

std::map<OgreBulletDynamics::RigidBody *, ObjBriquette *> & GestObj::getListRigidBodyToBriquette()
{
	return this->lstRigidBodyToBriquette;
}

ObjBriquette * GestObj::getBriquetteByRigidBody(OgreBulletDynamics::RigidBody * rigidBody)
{
	return this->lstRigidBodyToBriquette[rigidBody];
}


double GestObj::calculDistBriquetteEloigne(){
    std::vector<ObjBriquette *> lstBriquettes = this->getListBriquettes();
    std::vector<ObjBriquette *>::iterator it;
    double max=0;
    for(it = lstBriquettes.begin() ; it < lstBriquettes.end() ; it ++)
    {
        if((*it)->isDrawing()){
            //si le corps bullet n'est pas activé, c'est que la briquette est stable
            if(((*it)->getRigidBody()->getBulletRigidBody()->isActive())==false){
                max=std::max(max, (*it)->getRangeToCenter()-100);  
            }
        }
    }
    return max;
}
