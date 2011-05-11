#include "GestGame.h"

template<> GestGame * ClassRootSingleton<GestGame>::_instance = NULL;


GestGame::GestGame() : ClassRootSingleton<GestGame>()
{
    this->numberBriquetteInGame = 0;
    this->numberMaxBriquette = 0;
    this->gameLauched = false;
    this->positionCreationBriquette = Ogre::Vector3(0.0, 0.0, 0.0);
    
    
    ListenerFrame::getSingletonPtr()->signalFrameStarted.add(&GestGame::checkBriquette, this);
    
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&GestGame::onKeyPressed, this);
    PlayerControls::getSingletonPtr()->signalKeyReleased.add(&GestGame::onKeyReleased, this);
    PlayerControls::getSingletonPtr()->signalMouseMoved.add(&GestGame::onMouseMoved, this);
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
        
		GestObj * gest = GestObj::getSingletonPtr();
		
		gest->addBriquette(vec);
    
		this->addModification();
		
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


void GestGame::alignBriquettes()
{
    std::vector<ObjBriquette *>::iterator it;
    for(it = GestObj::getSingletonPtr()->getListBriquettes().begin() ; it < GestObj::getSingletonPtr()->getListBriquettes().end() ; it++)
    {
		Ogre::Vector3 vec = Ogre::Vector3((*it)->getSceneNode()->getPosition()[0], this->positionCreationBriquette[1], (*it)->getSceneNode()->getPosition()[2]);
		if((*it)->isDrawing())
		{
			(*it)->setPosition(vec);
			(*it)->setOrientation(ObjBriquette::defaultOrientation);
		
			(*it)->getRigidBody()->getBulletRigidBody()->forceActivationState(false);
			(*it)->getRigidBody()->getBulletRigidBody()->clearForces();
			(*it)->getRigidBody()->getBulletRigidBody()->activate(true);
		}
		else
		{
			(*it)->getSceneNode()->setPosition(vec);
			(*it)->getSceneNode()->setOrientation(ObjBriquette::defaultOrientation);
		}
	}
	
	this->addModification();
}

void GestGame::addModification()
{
	GestSnapShoot * gest = GestSnapShoot::getSingletonPtr();
	gest->addModification();

	if(Menus::getSingletonPtr()->getMenusBriquette() != NULL)
		Menus::getSingletonPtr()->getMenusBriquette()->updateTextButtons();
}

void GestGame::undo(unsigned int numberModification)
{
	GestSnapShoot * gest = GestSnapShoot::getSingletonPtr();
	gest->undo(numberModification);
	
	this->numberBriquetteInGame = GestObj::getSingletonPtr()->getCountBriquetteDrawed();

	if(Menus::getSingletonPtr()->getMenusBriquette() != NULL)
		Menus::getSingletonPtr()->getMenusBriquette()->updateTextButtons();
}

void GestGame::undoAll()
{
	GestSnapShoot * gest = GestSnapShoot::getSingletonPtr();
	gest->undoAll();

	this->numberBriquetteInGame = GestObj::getSingletonPtr()->getCountBriquetteDrawed();

	if(Menus::getSingletonPtr()->getMenusBriquette() != NULL)
		Menus::getSingletonPtr()->getMenusBriquette()->updateTextButtons();
}

void GestGame::redo(unsigned int numberModification)
{
	GestSnapShoot * gest = GestSnapShoot::getSingletonPtr();
	gest->redo(numberModification);
	
	this->numberBriquetteInGame = GestObj::getSingletonPtr()->getCountBriquetteDrawed();

	if(Menus::getSingletonPtr()->getMenusBriquette() != NULL)
		Menus::getSingletonPtr()->getMenusBriquette()->updateTextButtons();
}

void GestGame::redoAll()
{
	GestSnapShoot * gest = GestSnapShoot::getSingletonPtr();
	gest->redoAll();

	this->numberBriquetteInGame = GestObj::getSingletonPtr()->getCountBriquetteDrawed();

	if(Menus::getSingletonPtr()->getMenusBriquette() != NULL)
		Menus::getSingletonPtr()->getMenusBriquette()->updateTextButtons();
}

void GestGame::quitGame()
{
	ListenerFrame::getSingletonPtr()->shutdown();
}


void GestGame::moveCameraTargetOnBriquette()
{
	Ogre::Ray rayon;
	OgreBulletDynamics::RigidBody * body = MouseFunction::getSingletonPtr()->getBodyUnderCursorUsingBullet(rayon);
   
	if((body != NULL) && (!body->isStaticObject()))
	{
		ObjBriquette * briquette = GestObj::getSingletonPtr()->getBriquetteByRigidBody(body);
		
		if(briquette != NULL)
		{
			Ogre::Vector3 vec = briquette->getSceneNode()->getPosition();
			vec[2] = GestCamera::getSingletonPtr()->getCurrentCamera()->getTargetNode()->getPosition()[2];
			GestCamera::getSingletonPtr()->getCurrentCamera()->definePositionTarget(vec);
		}
	}
}


void GestGame::switchPhysicEngineState()
{
	
	ListenerCollision::getSingletonPtr()->physicEngineMutexLock(this);
	ListenerCollision::getSingletonPtr()->switchPhysicEngineState(this);
	ListenerCollision::getSingletonPtr()->physicEngineMutexUnLock(this);
	
	if(ListenerCollision::getSingletonPtr()->getPhysicEngineState())
	{
		std::vector<ObjBriquette *> lstBriquettes = GestObj::getSingletonPtr()->getListBriquettes();
		std::vector<ObjBriquette *>::iterator it;
		for(it = lstBriquettes.begin() ; it <lstBriquettes.end() ; it ++)
		{
			if((*it)->isDrawing())
			{
				(*it)->getRigidBody()->getBulletRigidBody()->activate(true);
			}
		}
	}
	
	if(Menus::getSingletonPtr()->getMenusBriquette() != NULL)
		Menus::getSingletonPtr()->getMenusBriquette()->updateTextButtons();
}


void GestGame::injectMouseMove(float delta_x, float delta_y)
{
	//permet de déplacer également la souris de Bullet
	MouseFunction::getSingletonPtr()->injectMouseMove(delta_x, delta_y);
	
	//permet de déplacer également la souris du menus CEGUI
	Menus::getSingletonPtr()->injectMouseMove(delta_x, delta_y);
}



void GestGame::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::SWITCH_BULLET_STATE:
			this->switchPhysicEngineState();
            break;
            
        case Controls::UNDO :
            this->undo();
            break;
            
        case Controls::REDO :
            this->redo();
            break;
            
        case Controls::UNDO_ALL :
            this->undoAll();
            break;
            
        case Controls::REDO_ALL :
            this->redoAll();
            break;
            
        case Controls::ADD_REVISION :
            this->addModification();
            break;
            
        case Controls::QUIT :
			this->quitGame();
            break;

        case Controls::MOUSE_CAMERA_ROTATE :
            this->moveCameraTargetOnBriquette();
            break;     
            
        case Controls::CALCUL_RES :
		{
			Menus::getSingletonPtr()->switch_menus_score();
            break;
		}   
        
        default:
            break;
    }
}


void GestGame::onKeyReleased(Controls::Controls key)
{
		
    switch(key)
    {     
        default:
            break;
    }
}


void GestGame::onMouseMoved(MouseMove_t &mouseMove)
{   
		
    switch(mouseMove.controlMouseId)
    {     
		case Controls::NONE :
		case Controls::SELECT :
		{
			this->injectMouseMove(mouseMove.vector[0], mouseMove.vector[1]);
			break;
		}
		
			
        default:
            break;
    }
}
