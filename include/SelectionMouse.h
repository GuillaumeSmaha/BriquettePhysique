/*!
*  \file  SelectionMouse.h
* \brief permet d'afficher un pointeur de souris et de selectionner des briquettes
*/
#ifndef __SELECTION_MOUSE_H__
#define __SELECTION_MOUSE_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#include <OgreBulletCollisions.h>
#include <OgreBulletDynamics.h>
#include <OgreBulletCollisionsShape.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsPreRequisites.h>
#endif

#include "mouseMove.h"
#include "collisionBullet.h"
#include "ClassRootSingleton.h"
#include "PlayerControls.h"
#include "ListenerCollision.h"
#include "MouseFunction.h"
#include "ObjBriquette.h"
#include "GestObj.h"
#include "GestGame.h"


/*!
* \class SelectionMouse
* \brief Class permettent d'afficher un pointeur de souris et de selectionner des briquettes (via lancé de rayon)
*/
class SelectionMouse: public ClassRootSingleton<SelectionMouse>
{
    private:
        /*!
         * \brief permet d'avoir la dernière briquette selectionné
         * c'est elle que l'on déplace
        */
        OgreBulletDynamics::RigidBody * selectedBriquetteOnMove;  
        /*!
         * \brief permet d'avoir la dernière briquette selectionné
         * c'est elle que l'on déplace
        */
        OgreBulletDynamics::RigidBody * selectedBriquettePrevious;  


	public:
        /*!
        * \brief Constructeur par défault, ne doit pas être utilisé
        */
        SelectionMouse();
        /*!
        * \brief Destructeur
        */
       ~SelectionMouse();

	private:
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
       
};


#endif //__SELECTION_MOUSE_H__
