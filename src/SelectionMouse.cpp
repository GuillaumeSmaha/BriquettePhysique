#include "SelectionMouse.h"


using namespace Ogre;

template<> SelectionMouse * ClassRootSingleton<SelectionMouse>::_instance = NULL;



SelectionMouse::SelectionMouse() : ClassRootSingleton<SelectionMouse>()
{
    this->selectedBriquetteOnMove = NULL;   
    this->selectedBriquettePrevious = NULL;   
    PlayerControls::getSingletonPtr()->signalMouseMoved.add(&SelectionMouse::onMouseMoved, this);
    PlayerControls::getSingletonPtr()->signalKeyPressed.add(&SelectionMouse::onKeyPressed, this);
    PlayerControls::getSingletonPtr()->signalKeyReleased.add(&SelectionMouse::onKeyReleased, this);
}


SelectionMouse::~SelectionMouse()
{


}


void SelectionMouse::onMouseMoved(MouseMove_t &mouseMove)
{
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
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallback = MouseFunction::getSingletonPtr()->getResultUnderCursorUsingBullet(rayon);
			
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
            
        case Controls::UNDO :
        case Controls::REDO :
            this->selectedBriquetteOnMove = NULL;
            this->selectedBriquettePrevious = NULL;
            break;
            
        case Controls::SELECT_MOVE_UP :
            if(this->selectedBriquettePrevious != NULL)
				GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquettePrevious)->move(Ogre::Vector3(0.0, 0.0, 0.5));
            break;
            
        case Controls::SELECT_MOVE_DOWN :
            if(this->selectedBriquettePrevious != NULL)
				GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquettePrevious)->move(Ogre::Vector3(0.0, 0.0, -0.5));
        
            break;
            
        case Controls::SELECT_MOVE_LEFT :
            if(this->selectedBriquettePrevious != NULL)
				GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquettePrevious)->move(Ogre::Vector3(0.5, 0.0, 0.0));
        
            break;
            
        case Controls::SELECT_MOVE_RIGHT :
            if(this->selectedBriquettePrevious != NULL)
				GestObj::getSingletonPtr()->getBriquetteByRigidBody(this->selectedBriquettePrevious)->move(Ogre::Vector3(-0.5, 0.0, 0.0));
        
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
		OgreBulletDynamics::RigidBody * body = MouseFunction::getSingletonPtr()->getBodyUnderCursorUsingBullet(rayon);
	   
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
        this->selectedBriquetteOnMove = NULL;
                
        GestGame::getSingletonPtr()->addModification();
     
        //mettre a jour la bounding permet de la placer à la nouvelle position de la briquette   
        GestObj::getSingletonPtr()->updateAllForces();
    }
}
