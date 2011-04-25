#include "GestGame.h"

template<> GestGame * ClassRootSingleton<GestGame>::_instance = NULL;


GestGame::GestGame() : ClassRootSingleton<GestGame>()
{
    this->numberBriquetteInGame = 0;
    this->numberMaxBriquette = 0;
    this->gameLauched = false;
    this->positionCreationBriquette = Ogre::Vector3(0.0, 0.0, 0.0);
    
    
    ListenerFrame::getSingletonPtr()->signalFrameStarted.add(&GestGame::checkBriquette, this);
    //~ PlayerControls::getSingletonPtr()->signalKeyPressed.add(&GestGame::onKeyPressed, GestGame::getSingletonPtr());
}


GestGame::~GestGame()
{
	
}

void GestGame::setDifficulty(GestGame::Difficulty difficulty)
{
	if(!this->gameLauched)
	{
		switch(difficulty)
		{
			case GestGame::DIFFICULTY_EASY :
				this->numberMaxBriquette = NB_BRIQ_EASY;
				break;
							
			case GestGame::DIFFICULTY_MEDIUM :
				this->numberMaxBriquette = NB_BRIQ_MEDIUM;
				break;
				
			case GestGame::DIFFICULTY_HARD :
				this->numberMaxBriquette = NB_BRIQ_HARD;
				break;
			
			default:
				this->numberMaxBriquette = NB_BRIQ_EASY;
				break;
		}
		
		this->numberBriquetteInGame = 0;
		
		this->gameLauched = true;
		
		Application::getSingletonPtr()->initScene();
	}
}


bool GestGame::addBriquette()
{
    if(this->numberBriquetteInGame < this->numberMaxBriquette)
    {
        this->numberBriquetteInGame++;
        Ogre::Vector3 vec = this->positionCreationBriquette + Ogre::Vector3(0.0, 0.0, 10.0);
		GestObj::getSingletonPtr()->addBriquette(vec);
		
    
		return true;
    }
    
    return false;
}


void GestGame::removeBriquette(ObjBriquette * briquette)
{
	this->numberBriquetteInGame--;
	briquette->hide();
}


void GestGame::checkBriquette(const Ogre::FrameEvent & null)
{
    std::vector<ObjBriquette *>::iterator it;
    for(it = GestObj::getSingletonPtr()->getListBriquettes().begin() ; it < GestObj::getSingletonPtr()->getListBriquettes().end() ; it++)
    {
		if((*it)->isDrawing() && (*it)->getSceneNode()->getPosition()[2] < -100)
		{
			Ogre::Vector3 vec = this->positionCreationBriquette + Ogre::Vector3(0.0, 0.0, 10.0);
			(*it)->setPosition(vec);
			(*it)->setOrientation(ObjBriquette::defaultOrientation);
		}
	}		
}

void GestGame::undo(unsigned int numberModification)
{
	GestSnapShoot::getSingletonPtr()->undo(numberModification);
	this->numberBriquetteInGame = GestObj::getSingletonPtr()->getCountBriquetteDrawed();
}

void GestGame::undoAll()
{
	GestSnapShoot::getSingletonPtr()->undoAll();
	this->numberBriquetteInGame = GestObj::getSingletonPtr()->getCountBriquetteDrawed();
}

void GestGame::redo(unsigned int numberModification)
{
	GestSnapShoot::getSingletonPtr()->redo(numberModification);
	this->numberBriquetteInGame = GestObj::getSingletonPtr()->getCountBriquetteDrawed();
}

void GestGame::redoAll()
{
	GestSnapShoot::getSingletonPtr()->redoAll();
	this->numberBriquetteInGame = GestObj::getSingletonPtr()->getCountBriquetteDrawed();
}

void GestGame::quitGame()
{
	ListenerFrame::getSingletonPtr()->shutdown();
}


void GestGame::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::UNDO:
            this->undo();
            break;
            
        case Controls::REDO:
            this->redo();
            break;
            
        case Controls::QUIT :
			this->quitGame();
            break;

        default:
            break;
    }
}
