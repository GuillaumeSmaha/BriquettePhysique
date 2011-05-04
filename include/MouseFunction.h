/*!
* \file MouseFunction.h
* \brief This file contains the declaration of a structure for mouse dragging
*/
#ifndef __MOUSE_FUNCTION_H__
#define __MOUSE_FUNCTION_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#include <OgreBulletCollisionsPreRequisites.h>
#include <OgreBulletCollisionsRay.h>
#include <OgreBulletDynamicsPreRequisites.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>
#endif

#include "GestCamera.h"
#include "ListenerCollision.h"


/*!
 * \class MouseFunction
 * \brief Classe permettant de gérer les functions de la souris
 */
class MouseFunction
{		
	private:
        /*!
         * \brief Constructor
        */
		MouseFunction();
		
        /*!
         * \brief Destructor
        */
		~MouseFunction();
		
		
	public:
        /*!
         * \brief Essaye d'attraper une briquette lors d'un clic de souris
         * \param rayTo Rayon à lancer
         * \param mouseScreenX Position en X de la souris sur l'écran
         * \param mouseScreenY Position en Y de la souris sur l'écran
         * \return L'objet percuté par le rayon ou NULL
        */
        static OgreBulletDynamics::RigidBody * getBodyUnderCursorUsingBullet(Ogre::Ray &rayTo, Ogre::Real mouseScreenX, Ogre::Real mouseScreenY);
        /*!
         * \brief Essaye d'attraper le résultat lors d'un clic de souris
         * Attention à supprimer le pointeur
         * \param rayTo Rayon à lancer
         * \param mouseScreenX Position en X de la souris sur l'écran
         * \param mouseScreenY Position en Y de la souris sur l'écran
         * \return Le résultat du lancer de rayon
        */
        static OgreBulletCollisions::CollisionClosestRayResultCallback * getResultUnderCursorUsingBullet(Ogre::Ray &rayTo, Ogre::Real mouseScreenX, Ogre::Real mouseScreenY);
};

#endif //__MOUSE_FUNCTION_H__
