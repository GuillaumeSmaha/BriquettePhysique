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
class MouseFunction : public ClassRootSingleton<MouseFunction>
{	
	public:
		/*!
		 * \brief NE PAS UTILISER, present uniquement pour la définition de ClassRootSingleton
         *  il faut utiliser createSingleton(Ogre::RenderWindow * win) à la place.
		*/		
        static void createSingleton();
        /*!
         * Permet de creer la souris, celle ci ce présente sous la forme d'un curseur qui peut saisir les briquettes.
         * \param win: Le renderWindow permet d'avoir la taille de la fenetre et donc d'adapter la taille du curseur à celle ci
        */
        static void createSingleton(Ogre::RenderWindow * win);
        
	private:        
        /*!
         * \brief Position de la souris
        */
        Ogre::Vector3 posMouse;
        /*!
         * \brief Permet de conserver la largeur la fenetre
        */
        int winWidth;
        /*!
         * \brief Permet de conserver la hauteur de la fenetre
        */
        int winHeight;
        
	private:
        /*!
         * \brief Constructor
        */
		MouseFunction();
		
        /*!
         * \brief Constructor
         * \param win Le renderWindow permet d'avoir la taille de la fenetre et donc d'adapter la taille du curseur à celle ci
        */
		MouseFunction(Ogre::RenderWindow * win);
		
        /*!
         * \brief Destructor
        */
		~MouseFunction();
		
	public:
        /*!
         * \brief Permet de déplacer la souris en lui injectant le vecteur x, y.
         * La souris n'est pas géré directement dans cette classe mais dans la
         * classe MouseFunction car en réalité on à 2 souris (la souris du
         * menus CEGUI et la souris de bullet pour attraper les briquettes.
         *
         * Cette fonction permet donc a GestGame de déplacer la souris de
         * Bullet pour que les deux ai la même position
         * \param delta_x Déplacement sur l'axe X
         * \param delta_y Déplacement sur l'axe Y
        */
        void injectMouseMove(float delta_x, float delta_y);
        
        /*!
         * \brief Essaye d'attraper une briquette lors d'un clic de souris
         * \param rayTo Rayon à lancer
         * \return L'objet percuté par le rayon ou NULL
        */
        OgreBulletDynamics::RigidBody * getBodyUnderCursorUsingBullet(Ogre::Ray &rayTo);
        /*!
         * \brief Essaye d'attraper le résultat lors d'un clic de souris
         * Attention à supprimer le pointeur
         * \param rayTo Rayon à lancer
         * \return Le résultat du lancer de rayon
        */
        OgreBulletCollisions::CollisionClosestRayResultCallback * getResultUnderCursorUsingBullet(Ogre::Ray &rayTo);
		
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
