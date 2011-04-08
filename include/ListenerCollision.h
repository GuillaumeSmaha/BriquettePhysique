/*!
 *  \file  ListenerCollision.h
 * \brief Ce fichier contient la déclaration de la classe ListenerCollision. C'est la classe gérant les collisions. On utilise la librairie OgreBullet
 */
#ifndef __LISTENER_COLLISION_H__
#define __LISTENER_COLLISION_H__

#include <iostream>
#include <Ogre.h>
#include <OgreBulletCollisionsPreRequisites.h>
#include <OgreBulletCollisionsRay.h>
#include <OgreBulletDynamicsPreRequisites.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>

#include "ClassRootSingleton.h"
#include "GestSceneManager.h"
#include "ListenerFrame.h"
#include "PlayerControls.h"

/*!
 * \class ListenerCollision
 * \brief Classe permettant de gérer les événements de collision
 */
class ListenerCollision : public ClassRootSingleton<ListenerCollision>
{		
	private:
		/*!
		 * \brief Définit le monde pour OgreBullet
		 */
		OgreBulletDynamics::DynamicsWorld * mWorld;
		/*!
		 * \brief Trace de débug pour OgreBullet
		 */
		OgreBulletCollisions::DebugDrawer * debugDrawer;
		/*!
		 * \brief Définit si le moteur physique est actif
		 */
		bool physicEngineState;
		/*!
		 * \brief Définit si le moteur physique est actif
		 */
		bool physicEngineMutex;
		/*!
		 * \brief Définit si le moteur physique est actif
		 */
		void * physicEngineMutexLocker;


	public:
		/*!
		 * \brief Constructor
		 */
		ListenerCollision();
		/*!
		 * \brief Destructor
		 */
		~ListenerCollision();
		
		/*!
		 * \brief Switch the value of the attribute physicEngineState
		 */
		bool switchPhysicEngineState(void * locker = NULL);
		
        /*!
         * \brief Permet de réagir a l'appui sur touche/button souris, permet de lancer la prise de briquettes
         * \param key Evénement du clavier
        */
        void onKeyPressed(Controls::Controls key);

		/*!
		 * \brief Met à jour les collision
		 * \param evt Evenement du controlleur de frame
		 */
		void updateCollision(const Ogre::FrameEvent &evt);
		
		
		/*!
		 * \brief Définit si le moteur physique est actif
		 */
		bool physicEngineMutexLock(void * locker);
		/*!
		 * \brief Définit si le moteur physique est actif
		 */
		void physicEngineMutexUnLock(void * locker);
		
		
		//Getter - Setter
		

		/*!
		 * \brief [Getter] Pointeur sur le monde d'ogreBullet
		 * \return Retourne un pointeur sur le monde d'ogreBullet
		 */
		OgreBulletDynamics::DynamicsWorld * getWorld()
		{
			return mWorld;
		}

		/*!
		 * \brief [Getter] Valeur de l'attribut physicEngineState
		 * \return Retourne l'état du moteur physique
		 */
		bool getPhysicEngineState()
		{
			return this->physicEngineState;
		}
		/*!
		 * \brief [Setter] Définit de l'attribut physicEngineState
		 * \param physicEngineState Définit l'état du moteur physique
		 */
		bool setPhysicEngineState(bool physicEngineState, void * locker = NULL);
};

#endif //__LISTENER_COLLISION_H__

