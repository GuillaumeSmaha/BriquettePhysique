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
    createOverlay(win);
    this->selectedBriquetteOnMove = NULL;   
    this->selectedBriquettePrevious = NULL;   
    PlayerControls::getSingletonPtr()->signalMouseMoved.add(&SelectionMouse::onMouseMoved, this);
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&SelectionMouse::onKeyPressed, this);
    PlayerControls::getSingletonPtr()->signalKeyReleased.add(&SelectionMouse::onKeyReleased, this);
}


SelectionMouse::~SelectionMouse()
{


}


void SelectionMouse::createOverlay(Ogre::RenderWindow * win)
{
	this->mouseOverlay = OverlayManager::getSingletonPtr()->create("GuiOverlay");
	this->mouseOverlay->setZOrder(600);
	this->mousePanel = (Ogre::OverlayElement *)OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIMouse");
	//this->mousePanel->setMaterialName("TargetSights");

	TexturePtr mouseTex = TextureManager::getSingleton().load("target.png", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	this->winWidth= win->getWidth();
	this->winHeight= win->getHeight();
	this->mousePanel->setWidth (mouseTex->getWidth() / (float)this->winWidth); 
	this->mousePanel->setHeight (mouseTex->getHeight() / (float)this->winHeight);

	//la souris est centré initialement
	this->posMouse[0] = 0.5 - mousePanel->getWidth() / 2.0;        //correspond à la position horizontale
	this->posMouse[1] = 0.5 - mousePanel->getHeight() / 2.0;        //correspond à la position verticale
	this->mousePanel->setPosition(this->posMouse[0], this->posMouse[1]);
  
	Ogre::OverlayContainer * mouseContainer = (Ogre::OverlayContainer*)OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "GUIContainer");
	this->mouseOverlay->add2D(mouseContainer);
	mouseContainer->addChild(this->mousePanel);
	this->mouseOverlay->show(); 
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
        if(posMouse[0] < (0.0 - this->mousePanel->getWidth() / 2.0))
        {
            this->posMouse[0] = 0.0 - this->mousePanel->getWidth()/2;
        }
        if(posMouse[0] > (1.0 - this->mousePanel->getWidth() / 2.0))
        {
            this->posMouse[0] = 1.0 - this->mousePanel->getWidth()/2;
        }

        //réglage vertical
		this->posMouse[1] = this->posMouse[1] + (mouseMove.vector[1] / this->winHeight);

        //Ces conditions permettent d'éviter que la souris ne sorte de la fenetre
        //C'est nécéssaire car la souris CEGUI est prévu pour ne pas sortir de la fenetre, 
        //on perd donc la correspondance si l'une sort et pas l'autre
        if(posMouse[1] < (0.0 - this->mousePanel->getHeight() / 2.0))
        {
            this->posMouse[1] = 0.0 - this->mousePanel->getHeight() / 2.0;
        }
        if(posMouse[1] > (1.0 - this->mousePanel->getHeight() / 2.0))
        {
            this->posMouse[1] = 1.0 - this->mousePanel->getHeight() / 2.0;
        }

        this->mousePanel->setPosition(posMouse[0], posMouse[1]);
	
		//permet de déplacer également la souris du menus CEGUI
		Menus::getSingletonPtr()->injectMouseMove(mouseMove.vector[0], mouseMove.vector[1]);
	}
	
	if(mouseMove.controlMouseId == Controls::SELECT)
	{
        if(this->selectedBriquetteOnMove != NULL)
        {
			//~ Ogre::Vector3 plan = Ogre::Vector3(50.0, 3.0, 50.0);
			Ogre::Vector3 plan = Ogre::Vector3(1000.0, 3.0, 1000.0);
			
			ObjBriquette * briquette = GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquetteOnMove);
			Ogre::SceneNode * nodeTest = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_TESTS);
			
			OgreBulletCollisions::CollisionShape * shapeTest = new OgreBulletCollisions::BoxCollisionShape(plan);
			
			//~ OgreBulletDynamics::RigidBody * bodyTest = new OgreBulletDynamics::RigidBody("RigidBodyTest", ListenerCollision::getSingletonPtr()->getWorld());
			OgreBulletDynamics::RigidBody * bodyTest = new OgreBulletDynamics::RigidBody("RigidBodyTest", ListenerCollision::getSingletonPtr()->getWorld(), COL_TEST_PLANE, TEST_PLANE_COLLIDES_WITH);
			
			bodyTest->setShape(nodeTest, shapeTest, 0.6, 0.6, 0.0, GestGame::getSingletonPtr()->getPositionCreationBriquette(), ObjBriquette::defaultOrientation);
            		
			Ogre::Ray rayon;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallback = this->getResultUnderCursorUsingBullet(rayon);
			
			if (mCollisionClosestRayResultCallback->doesCollide())
			{
				OgreBulletDynamics::RigidBody * body = static_cast<OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallback->getCollidedObject());
				
				if(body->getName() == "RigidBodyTest")
				{
					//~ this->selectedBriquetteOnMove->setPosition(
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
				this->clearAllForces();
		 
				std::cout << "body: " << this->selectedBriquetteOnMove->getName() << std::endl;
				std::cout << "orientation : " << briquette->getSceneNode()->getOrientation() << std::endl;
				std::cout << "orientation bullet : " << *(this->selectedBriquetteOnMove->getBulletRigidBody()->getOrientation()) << std::endl;
				//~ this->selectedBriquetteOnMove->getBulletRigidBody()->setOrientation(0.0);
				
				//std::cout << "orientation : " << *(this->selectedBriquetteOnMove->getBulletRigidBody()->getOrientation()) << std::endl;
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
	 
//        GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquetteOnMove)
//            ->getSceneNode()->setOrientation(ObjBriquette::defaultOrientation);
//
//        this->selectedBriquetteOnMove->getBulletRigidBody()->getWorldTransform().
//                setBasis(btMatrix3x3(btQuaternion(0,0,0,1)));
//
	
        ObjBriquette::updateBtBoundingBox(this->selectedBriquetteOnMove);
        
        
        this->selectedBriquetteOnMove = NULL;
                
        GestGame::getSingletonPtr()->addModification();
    }
}


void SelectionMouse::clearAllForces()
{
    std::vector<ObjBriquette *> lstBriquettes = GestObj::getSingletonPtr()->getListBriquettes();
    std::vector<ObjBriquette *>::iterator it;
    for(it = lstBriquettes.begin() ; it <lstBriquettes.end() ; it ++)
    {
		if((*it)->isDrawing())
		{
			(*it)->getRigidBody()->getBulletRigidBody()->forceActivationState(false);
			(*it)->getRigidBody()->getBulletRigidBody()->clearForces();
		}
    }
}



OgreBulletDynamics::RigidBody * SelectionMouse::getBodyUnderCursorUsingBullet(Ogre::Ray &rayTo)
{
    Ogre::Real mouseScreenX = this->posMouse[0] + (this->mousePanel->getWidth() / 2.0);
    Ogre::Real mouseScreenY = this->posMouse[1] + (this->mousePanel->getHeight() / 2.0);
    
    return MouseFunction::getBodyUnderCursorUsingBullet(rayTo, mouseScreenX, mouseScreenY);
}


OgreBulletCollisions::CollisionClosestRayResultCallback * SelectionMouse::getResultUnderCursorUsingBullet(Ogre::Ray &rayTo)
{
    Ogre::Real mouseScreenX = this->posMouse[0] + (this->mousePanel->getWidth() / 2.0);
    Ogre::Real mouseScreenY = this->posMouse[1] + (this->mousePanel->getHeight() / 2.0);
    
    return MouseFunction::getResultUnderCursorUsingBullet(rayTo, mouseScreenX, mouseScreenY);
}
