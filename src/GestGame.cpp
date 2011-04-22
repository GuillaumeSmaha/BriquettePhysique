#include "GestGame.h"

template<> GestGame * ClassRootSingleton<GestGame>::_instance = NULL;


GestGame::GestGame() : ClassRootSingleton<GestGame>()
{
    this->numberBriquetteInGame = 0;
    this->numberMaxBriquette = 0;
    this->gameLauched = false;
    this->positionCreationBriquette = Ogre::Vector3(0.0, 0.0, 0.0);
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


void GestGame::quitGame()
{
	ListenerFrame::getSingletonPtr()->shutdown();
	//~ Application::getSingletonPtr()->killApplication();
}


void GestGame::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::QUIT :
			this->quitGame();
            break;

        default:
            break;
    }
}
