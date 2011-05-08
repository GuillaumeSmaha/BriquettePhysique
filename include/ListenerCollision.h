/*!
 *  \file  ListenerCollision.h
 * \brief Ce fichier contient la déclaration de la classe ListenerCollision. C'est la classe gérant les collisions. On utilise la librairie OgreBullet
 */
#ifndef __LISTENER_COLLISION_H__
#define __LISTENER_COLLISION_H__

#ifndef DOXYGEN_SKIP
#include <iostream>
#include <Ogre.h>
#include <OgreBulletCollisionsPreRequisites.h>
#include <OgreBulletCollisionsRay.h>
#include <OgreBulletDynamicsPreRequisites.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>
#endif

#include "ClassRootSingleton.h"
#include "GestSceneManager.h"
#include "ListenerFrame.h"

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
		 * \brief Met à jour les collision
		 * \param evt Evenement du controlleur de frame
		 */
		void updateCollision(const Ogre::FrameEvent &evt);
		
		
		/*!
		 * \brief Définit si le moteur physique est actif
		 * \param locker Pointeur vers l'objet demandant l'utilisation
		 * \return Retourne si la modification a été autorisé
		 */
		bool physicEngineMutexLock(void * locker);
		/*!
		 * \brief Définit si le moteur physique est actif
		 * \param locker Pointeur vers l'objet demandant l'utilisation
		 * \return Retourne si la modification a été autorisé
		 */
		void physicEngineMutexUnLock(void * locker);
		
		/*!
		 * \brief Switch the value of the attribute physicEngineState
		 * \param locker Pointeur vers l'objet demandant l'utilisation
		 * \return Retourne si la modification a été autorisé
		 */
		bool switchPhysicEngineState(void * locker = NULL);
		
		/*!
		 * \brief [Setter] Définit de l'attribut physicEngineState
		 * \param physicEngineState Définit l'état du moteur physique
		 * \param locker Pointeur vers l'objet demandant l'utilisation
		 * \return Retourne si la modification a été autorisé
		 */
		bool setPhysicEngineState(bool physicEngineState, void * locker = NULL);
		
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
};

#endif //__LISTENER_COLLISION_H__

