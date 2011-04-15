#ifndef __MENUS_H__
#define __MENUS_H__


#include "controls.h"
#include "PlayerControls.h"
#include "Application.h"
#include "Fenetre.h"
#include "ClassRootSingleton.h"

class PlayerControls;
class Menus: public ClassRootSingleton<Menus>, Fenetre
{
    private:
        /*!
        * \brief le renderer de cegui pour ogre
        */
        CEGUI::OgreRenderer * menusRenderer;
         /*!
         * \brief Pointeur sur le controleur du clavier
         */
        ListenerKeyboard * keyControl;
         /*!
         * \brief Pointeur sur le controleur de la souris
         */
        ListenerMouse * mouseControl;
         /*!
         * \brief Pointeur sur le controleur du joueur
         */
        PlayerControls * pControl;
         /*!
         * \brief Indique si le menu est ouvert
         */
        bool menu_open;
    public:
         /*!
        * \brief Dispatché quand mis en pause ou reprise
        */
        Signal<bool> signalPaused;
        /*!
        * \brief constructeur
        */
        Menus();
        /*!
        * \brief destructeur
        */
        ~Menus();

        /*!
         * \brief Lance l'affichage des différents éléments du menus lors de l'activation de celui ci
         */
        void afficher_menus();

        /*!
         * \brief Permet de déplacer la souris en lui injectant le vecteur x, y.
         * La souris n'est pas géré directement dans cette classe mais dans la
         * classe SelectionMouse car en réalité on à 2 souris (la souris du
         * menus CEGUI et la souris de bullet pour attraper les briquettes.
         *
         * Cette fonction permet donc a SelectionMouse de déplacer la souris de
         * CEGUI pour que les deux ai la même position
        */
        void injectMouseMove (float delta_x, float delta_y);

    private:
        /*!
         * \brief Permet de récupérer appuis sur touche dans cegui
        */
        void keyPressed(const OIS::KeyEvent &evt);

        /*!
         * \brief Permet de récupérer les relachements d'une touche dans cegui
        */
        void keyReleased(const OIS::KeyEvent &evt);


        /*!
         * \brief Permet de récupérer les relachement de touche dans cegui
        */
        void keyReleased(OIS::MouseButtonID evt);

        /*!
         * \brief Permet de récupérer les clics de souris dans cegui
        */
        void mousePressed(OIS::MouseButtonID evt);

        /*!
         * \brief Permet de récupérer les relachements de la souris dans cegui
        */
        void mouseReleased(OIS::MouseButtonID evt);

        /*!
         * \brief Permet de récupérer les déplacements de la souris
        */
        void mouseMoved(MouseMove_t &mouse);

        /*!
         * \brief Permet de convertir les clics de souris pour cegui (utilisé par mousePressed).
        */
        CEGUI::MouseButton convertButton(OIS::MouseButtonID evt);

        /*!
        * \brief Réagis aux actions de player, en particulier pour gérer l'ouverture/fermeture du menus
        */

        void actionFromPlayer(Controls::Controls key);
        /*!
         * \brief Retire le menus lorsque l'on le quitte.
         */
        void cacher_menus();

        /*!
         * \brief Crée le menus principal
         */
        void creer_main_window(void);

        /*!
         * \brief Crée le menus principal
         */
        void creer_menus_start(void);

        /*!
         * \brief Affiche le menus principal
         */
        void afficher_main_window(void);
        /*!
         * \brief Cache le menus principal
         */
        void cacher_main_window(void);

        /*!
        * \brief Permet d'afficher un curseur de souris
        */
        void creer_souris(void);

        /*!
         * \brief Affiche la souris
         */
        void afficher_souris(void);

        /*!
         * \brief cache la souris
        */
        void cacher_souris(void);
        /*!
        * \brief Permet de supprimer une fenetre (appeler par create_std_window, ne devrait pas être utilisé ailleurs).
        */
        bool destroyWindow(const CEGUI::EventArgs & evt);
         /*!
        * \brief Permet de démarrer le jeux en mode facile
        */       
        bool startFacile(const CEGUI::EventArgs & evt);
        /*!
        * \brief Permet de démarrer le jeux en mode moyen
        */
        bool startMedium(const CEGUI::EventArgs & evt);
        /*!
        * \brief Permet de démarrer le jeux en mode difficile
        */
        bool startDifficile(const CEGUI::EventArgs & evt);

        
};


#endif//__MENUS_H__
