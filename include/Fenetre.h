/*!
*  \file  Fenetre.h
*  \brief Ce fichier contient la déclaration de la classe Fenetre. Elle utilise cegui pour offrir des fenetre standard. Utiliser par le Menus et Annonce
*/
#ifndef __FENETRE_H__
#define __FENETRE_H__

#ifndef DOXYGEN_SKIP
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#endif

#include "PlayerControls.h"

/*!
* \class Fenetre
* \brief Elle utilise cegui pour offrir des fenetre standard. Utiliser par le Menus et Annonce
*/
class Fenetre
{
    protected:
        /*!
        * \brief fenetre principale de l'application
        */
        CEGUI::Window * mainWdw;
         /*!
        * \brief Dispatché quand mis en pause ou reprise
        */
        Signal<bool> signalPaused;


    protected:
        /*!
        * \brief Permet de créer une fentre de menus générique
        */
        CEGUI::Window * create_std_window(CEGUI::utf8 * name, float posX, float posY ,float largeur, float hauteur, int nbEl, CEGUI::Window ** contenu);

        /*!
        * \brief action lors de la fermeture de la fenetre avec le bouton fermer
        */
        virtual bool actionButtonClose(const CEGUI::EventArgs & evt);

        /*!
        * \brief Permet de supprimer une fenetre (appeler par create_std_window, ne devrait pas être utilisé ailleurs).
        */
        virtual bool destroyWindow(const CEGUI::EventArgs & evt) = 0;

        /*!
        * \brief Réagis aux actions de player, en particulier pour gérer l'ouverture/fermeture du menus
        * \param key Action appelé par le joueur
        */
        virtual void actionFromPlayer(Controls::Controls key) = 0;
};

#endif // __FENETRE_H__

