

/*!
*  \file  Application.h
*  \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
*/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__


#include <Ogre.h>

#include "ListenerWindow.h"
#include "ListenerMouse.h"
#include "ListenerKeyboard.h"
#include "ListenerFrame.h"

/*!
* \class Application
* \brief Class principale qui permet de démarrer le programme, d'afficher la fenêtre et de réagir aux évènements (ceux-ci sont ensuite dirigé vers les classes adaptés)
*
*   En particulier elle hérite de:
*   Ogre::FrameListener : Permet de recevoir les notifications avant et aprés chaque frame rendu à l'écran
*
*   Ogre::WindowEventListener : Permet d'obtenir les informations de déplacement/redimmensionnement de la fenetre ainsi que sa demande de fermeture
*
*   OIS::KeyListener : Information sur les évènements claviers
*
*   OIS::MouseListener
*/
class Application 
{
	private:
		/*!
		*  \brief Ogre Root
		*/
		Ogre::Root * root;
		/*!
		*  \brief Scène Manager
		*/
		Ogre::SceneManager * sceneMgr;
		/*!
		*  \brief Chemin du fichier resources.cfg
		*/
		Ogre::String resourcesCfg;
		/*!
		*  \brief Chemin du fichier plugins.cfg
		*/
		Ogre::String pluginsCfg;

		/*!
		* \brief GUI pour afficher les stats
		*/
		Ogre::Overlay * debugOverlay;

		/*!
		*  \brief Capteur d'événements
		*/
		OIS::InputManager * inputManager;

		/*!
		* \brief Listener pour les événements fenetre
		*/
		ListenerWindow * listenerWindow;
		/*!
		* \brief Listener pour les événements souris
		*/
		ListenerMouse * listenerMouse;
		/*!
		* \brief Listener pour les événements clavier
		*/
		ListenerKeyboard * listenerKeyboard;
		/*!
		* \brief Listener pour les événements rendu
		*/
		ListenerFrame * listenerFrame;

		/*!
		* \brief Texte utile pour le debug
		*/
		Ogre::String debugText;


    public:

    	/*!
		*  \brief Définit si on affiche les stats
		*/
		bool isStatsOn;
    	/*!
		*  \brief Définit si on arrête le jeu
		*/
		bool shutDown;

    public:

        /*!
         * \brief constructeur
        */
        Application();
        /*!
         * \brief destructeur
        */
        ~Application();
        /*!
         * \brief demarrage du programme
        */
        bool start();

        /*!
         * \brief mise à jour des statistiques (nb frames...)
        */
        void updateStats(void *);
    
        /*!
         * \brief charge les ressources du projet (mesh, material...)
        */
        void loadRessources();

         /*!
         * \brief charge les ressources du projet (mesh, material...)
        */
        void initListeners();

         /*!
         * \brief Charge le graphe de scene
        */
        void initSceneGraph();
		/*!
		* \brief Affiche l'overlay des stats
		*/
		void showDebugOverlay(bool);


};

#endif 
