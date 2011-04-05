/*!
 *  \file  ListenerCollision.h
 * \brief Ce fichier contient la déclaration de la classe ListenerCollision. C'est la classe gérant les collisions. On utilise la librairie OgreBullet
 */
#ifndef __LISTENER_COLLISION_H__
#define __LISTENER_COLLISION_H__

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
		void setPhysicEngineState(bool physicEngineState)
		{
			this->physicEngineState = physicEngineState;
		}
};

#endif //__LISTENER_COLLISION_H__

