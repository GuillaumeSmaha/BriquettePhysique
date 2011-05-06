#include "SelectionMouse.h"


using namespace Ogre;

template<> SelectionMouse * ClassRootSingleton<SelectionMouse>::_instance = NULL;


void SelectionMouse::createSingleton()
{
    std::cerr << "Le constructeur de SelectionMouse ne doit pas être appelé via \
        createSingleton() et doit être appelé avec un Ogre::RenderWindow * en argument \
        !" << std::endl << "Attention le singleton n'ayant pas été crée, il est fort \
        possible d'avoir des erreurs de segmentation"  << std::endl ;
}

void SelectionMouse::createSingleton(Ogre::RenderWindow * win)
{
    new SelectionMouse(win);
}



SelectionMouse::SelectionMouse(Ogre::RenderWindow * win) : ClassRootSingleton<SelectionMouse>()
{
    initMouse(win);
    this->selectedBriquetteOnMove = NULL;   
    this->selectedBriquettePrevious = NULL;   
    PlayerControls::getSingletonPtr()->signalMouseMoved.add(&SelectionMouse::onMouseMoved, this);
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&SelectionMouse::onKeyPressed, this);
    PlayerControls::getSingletonPtr()->signalKeyReleased.add(&SelectionMouse::onKeyReleased, this);
}


SelectionMouse::~SelectionMouse()
{


}


void SelectionMouse::initMouse(Ogre::RenderWindow * win)
{
	this->winWidth= win->getWidth();
	this->winHeight= win->getHeight();

	//la souris est centré initialement
	this->posMouse[0] = 0.5;        //correspond à la position horizontale
	this->posMouse[1] = 0.5;        //correspond à la position verticale
  
}


void SelectionMouse::onMouseMoved(MouseMove_t &mouseMove)
{
	if(mouseMove.controlMouseId == Controls::NONE || mouseMove.controlMouseId == Controls::SELECT)
	{
        //réglage horizontal
		this->posMouse[0] = this->posMouse[0] + (mouseMove.vector[0]/this->winWidth);

        //Ces conditions permettent d'éviter que la souris ne sorte de la fenetre
        //C'est nécéssaire car la souris CEGUI est prévu pour ne pas sortir de la fenetre, 
        //on perd donc la correspondance si l'une sort et pas l'autre
        if(posMouse[0] < (0.0))
        {
            this->posMouse[0] = 0.0;
        }
        if(posMouse[0] > (1.0))
        {
            this->posMouse[0] = 1.0;
        }

        //réglage vertical
		this->posMouse[1] = this->posMouse[1] + (mouseMove.vector[1] / this->winHeight);

        //Ces conditions permettent d'éviter que la souris ne sorte de la fenetre
        //C'est nécéssaire car la souris CEGUI est prévu pour ne pas sortir de la fenetre, 
        //on perd donc la correspondance si l'une sort et pas l'autre
        if(posMouse[1] < (0.0))
        {
            this->posMouse[1] = 0.0;
        }
        if(posMouse[1] > (1.0))
        {
            this->posMouse[1] = 1.0;
        }

		//permet de déplacer également la souris du menus CEGUI
		Menus::getSingletonPtr()->injectMouseMove(mouseMove.vector[0], mouseMove.vector[1]);
	}
	
	if(mouseMove.controlMouseId == Controls::SELECT)
	{
        if(this->selectedBriquetteOnMove != NULL)
        {
			Ogre::Vector3 plan = Ogre::Vector3(1000.0, 3.0, 1000.0);
			
			ObjBriquette * briquette = GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquetteOnMove);
			Ogre::SceneNode * nodeTest = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_TESTS);
			
			OgreBulletCollisions::CollisionShape * shapeTest = new OgreBulletCollisions::BoxCollisionShape(plan);
			
			OgreBulletDynamics::RigidBody * bodyTest = new OgreBulletDynamics::RigidBody("RigidBodyTest", ListenerCollision::getSingletonPtr()->getWorld(), COL_TEST_PLANE, TEST_PLANE_COLLIDES_WITH);
			
			bodyTest->setShape(nodeTest, shapeTest, 0.0, 0.0, 0.0, GestGame::getSingletonPtr()->getPositionCreationBriquette(), ObjBriquette::defaultOrientation);
            		
			Ogre::Ray rayon;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallback = this->getResultUnderCursorUsingBullet(rayon);
			
			if (mCollisionClosestRayResultCallback->doesCollide())
			{
				OgreBulletDynamics::RigidBody * body = static_cast<OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallback->getCollidedObject());
				
				if(body->getName() == "RigidBodyTest")
				{
					briquette->setPosition(
						Ogre::Vector3(
							mCollisionClosestRayResultCallback->getCollisionPoint()[0],
							GestGame::getSingletonPtr()->getPositionCreationBriquette()[1],
							mCollisionClosestRayResultCallback->getCollisionPoint()[2]
						)
					);
				}
			}
            //permet que l'objet soit correctement orienté               
            GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquetteOnMove)->getSceneNode()->setOrientation(ObjBriquette::defaultOrientation);

            this->selectedBriquetteOnMove->getBulletRigidBody()->getWorldTransform().setBasis(btMatrix3x3(OgreBulletCollisions::OgreBtConverter::to(ObjBriquette::defaultOrientation)));

			this->selectedBriquetteOnMove->getBulletRigidBody()->forceActivationState(false);
			this->selectedBriquetteOnMove->getBulletRigidBody()->clearForces();

			delete mCollisionClosestRayResultCallback;            
            delete shapeTest;
            delete bodyTest;
        }
    }
}

void SelectionMouse::onKeyPressed(Controls::Controls key)
{
    switch(key)
    {
        case Controls::SELECT:
            this->selectBriquette();
            break;
            
        case Controls::UNDO:
        case Controls::REDO:
            this->selectedBriquetteOnMove = NULL;
            this->selectedBriquettePrevious = NULL;
            break;
            
        default:
            break;
    }
}

void SelectionMouse::onKeyReleased(Controls::Controls key)
{
    switch(key)
    {
        case Controls::SELECT:
            unselectBriquette();
            break;
            
        default:
            break;
    }
}


void SelectionMouse::selectBriquette()
{
	if(GestGame::getSingletonPtr()->getGameLauched())
	{
		Ogre::Ray rayon;
		OgreBulletDynamics::RigidBody * body = this->getBodyUnderCursorUsingBullet(rayon);
	   
		if((body != NULL) && (!body->isStaticObject()))
		{
			ObjBriquette * briquette = GestObj::getSingletonPtr()->getBriquetteByRigidBody(body);
			
			if(briquette != NULL)
			{
				if(this->selectedBriquettePrevious != NULL)
					GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquettePrevious)->setMaterielUnselected();
				
				this->selectedBriquetteOnMove = body;
				this->selectedBriquettePrevious = body;
				
				briquette->setMaterielSelected();
				
				body->getBulletRigidBody()->forceActivationState(false);
				GestObj::getSingletonPtr()->clearAllForces();
		 
				std::cout << "body: " << this->selectedBriquetteOnMove->getName() << std::endl;
				std::cout << "orientation : " << briquette->getSceneNode()->getOrientation() << std::endl;
				std::cout << "orientation bullet : " << *(this->selectedBriquetteOnMove->getBulletRigidBody()->getOrientation()) << std::endl;
			}
		}
		else
		{
			if(this->selectedBriquettePrevious != NULL)
			{
				GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquettePrevious)->setMaterielUnselected();
				
				this->selectedBriquettePrevious = NULL;
			}
		}
	}
}


void SelectionMouse::unselectBriquette()
{
    if(this->selectedBriquetteOnMove != NULL)
    {
        //mettre a jour la bounding permet de la placer à la nouvelle position de la briquette
        ObjBriquette::updateBtBoundingBox(this->selectedBriquetteOnMove);
           
        this->selectedBriquetteOnMove = NULL;
                
        GestGame::getSingletonPtr()->addModification();
    }
}



OgreBulletDynamics::RigidBody * SelectionMouse::getBodyUnderCursorUsingBullet(Ogre::Ray &rayTo)
{
    Ogre::Real mouseScreenX = this->posMouse[0];
    Ogre::Real mouseScreenY = this->posMouse[1];    
    return MouseFunction::getBodyUnderCursorUsingBullet(rayTo, mouseScreenX, mouseScreenY);
}


OgreBulletCollisions::CollisionClosestRayResultCallback * SelectionMouse::getResultUnderCursorUsingBullet(Ogre::Ray &rayTo)
{
    Ogre::Real mouseScreenX = this->posMouse[0];
    Ogre::Real mouseScreenY = this->posMouse[1]; 
   
    return MouseFunction::getResultUnderCursorUsingBullet(rayTo, mouseScreenX, mouseScreenY);
}
