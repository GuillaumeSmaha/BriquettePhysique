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
        static void createSingleton(Ogre::RenderWindow * win);
        /*  
        * Constructeur
        */
        SelectionMouse();
        SelectionMouse(Ogre::RenderWindow * win);
        ~SelectionMouse(){};


    private:
        Ogre::Overlay * mouseOverlay;
        Ogre::OverlayElement * mousePanel;


        Ogre::Vector2 posMouse;
        int winWidth, winHeight;
        /*
         * \brief cree l'overlay de la souris (affichage, texture...)
        */
        void createOverlay(Ogre::RenderWindow * win);

        /*
         * \brief permet de déplacer la souris sur l'écran
        */
        void onMouseMoved(Ogre::Vector3 mouseVec);
};


#endif//__SELECTION_MOUSE_H__
