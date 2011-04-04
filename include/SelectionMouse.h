/*!
*  \file  SelectionMouse.h
* \brief permet d'afficher un pointeur de souris et de selectionner des briquettes
*/
#ifndef __SELECTION_MOUSE_H__
#define __SELECTION_MOUSE_H__

#include <Ogre.h>
#include "ClassRootSingleton.h"
#include "PlayerControls.h"

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
       ~SelectionMouse(){};


    private:
        /*
         * Overlay ne contenant que le curseur de la souris
        */
        Ogre::Overlay * mouseOverlay;
        /*
         * pannel contenant la texture de la souris
        */
        Ogre::OverlayElement * mousePanel;

        /*
         * position de la souris
        */
        Ogre::Vector2 posMouse;

        /*
         * Permet de conserver la largeur et la hauteur de la fenetre
        */
        int winWidth, winHeight;


        /*  
        * Constructeur par défault, ne doit pas être utilisé
        */
        SelectionMouse();
        /*  
        * Constructeur 
        * \param win: Le renderWindow permet d'avoir la taille de la fenetre et donc d'adapter la taille du curseur à celle ci
        */
        SelectionMouse(Ogre::RenderWindow * win);
 

        /*
         * \brief cree l'overlay de la souris (affichage, texture...)
         * \param win: Le renderWindow permet d'avoir la taille de la fenetre et donc d'adapter la taille du curseur à celle ci
        */
        void createOverlay(Ogre::RenderWindow * win);

        /*
         * \brief permet de déplacer la souris sur l'écran
        */
        void onMouseMoved(Ogre::Vector3 mouseVec);
};


#endif//__SELECTION_MOUSE_H__
