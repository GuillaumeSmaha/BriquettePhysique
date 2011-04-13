/*!
*  \file  SelectionMouse.h
* \brief permet d'afficher un pointeur de souris et de selectionner des briquettes
*/
#ifndef __SELECTION_MOUSE_H__
#define __SELECTION_MOUSE_H__

#include <Ogre.h>
#include <OgreBulletCollisions.h>
#include <OgreBulletDynamics.h>
#include <OgreBulletCollisionsShape.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsPreRequisites.h>

#include "mouseMove.h"
#include "ClassRootSingleton.h"
#include "PlayerControls.h"
#include "CameraAbstract.h"
#include "GestCamera.h"
#include "ListenerCollision.h"
#include "GestSnapShoot.h"

/*!
* \class SelectionMouse
* \brief Class permettent d'afficher un pointeur de souris et de selectionner des briquettes (via lancé de rayon)
*/

class SelectionMouse: public ClassRootSingleton<SelectionMouse>
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
         * \brief permet d'avoir la dernière briquette selectionné
         * c'est elle que l'on déplace
        */
        OgreBulletDynamics::RigidBody * selectedBriquette;  

       /*!
         * \brief Overlay ne contenant que le curseur de la souris
        */
        Ogre::Overlay * mouseOverlay;
        /*!
         * \brief Panel contenant la texture de la souris
        */
        Ogre::OverlayElement * mousePanel;
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
        * \brief Constructeur par défault, ne doit pas être utilisé
        */
        SelectionMouse();
        /*! 
        * \brief Constructeur 
        * \param win: Le renderWindow permet d'avoir la taille de la fenetre et donc d'adapter la taille du curseur à celle ci
        */
        SelectionMouse(Ogre::RenderWindow * win);
        /*!
        * \brief Destructeur
        */
       ~SelectionMouse();

        /*!
         * \brief Crée l'overlay de la souris (affichage, texture...)
         * \param win Le renderWindow permet d'avoir la taille de la fenetre et donc d'adapter la taille du curseur à celle ci
        */
        void createOverlay(Ogre::RenderWindow * win);

        /*!
         * \brief Permet de déplacer la souris sur l'écran
		 * \param mouseMove Structure de déplacement de la souris
        */
        void onMouseMoved(MouseMove_t &mouseMove);
        /*!
         * \brief Permet de réagir a l'appui sur touche/button souris, permet de lancer la prise de briquettes
         * \param key Evénement du clavier
        */
        void onKeyPressed(Controls::Controls key);
        /*!
         * \brief Permet de réagir au relachement d'une touche/button souris.
         * \param key Evénement du clavier
        */
        void onKeyReleased(Controls::Controls key);
        /*!
         * \brief Essaye d'attraper une briquette lors d'un clic de souris
        */
        void selectBriquette();
        /*!
         * \brief Permet en particulier de reprendre le comportement physique de la briquette aprés mise à jour de sa position
        */
        void unselectBriquette();
        /*!
         * \brief Essaye d'attraper une briquette lors d'un clic de souris
         * \param rayTo Rayon à lancer
        */
        OgreBulletDynamics::RigidBody * getBodyUnderCursorUsingBullet(Ogre::Ray rayTo);
};


#endif //__SELECTION_MOUSE_H__
