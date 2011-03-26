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
#include "ListenerFrame.h"
#include "GestSceneManager.h"

class ObjectRoot;

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


	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerCollision();
		/*!
		 * \brief Constructeur
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
};

#endif //__LISTENER_COLLISION_H__

