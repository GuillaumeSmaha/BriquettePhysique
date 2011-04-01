/*!
*  \file  Application.h
* \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
*/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__


#include <Ogre.h>
#include "controls.h"
#include "nodeName.h"
#include "ClassRootSingleton.h"
#include "Utils.h"
#include "GestSceneManager.h"
#include "GestViewport.h"
#include "GestCamera.h"
#include "GestObj.h"
#include "ListenerWindow.h"
#include "ListenerFrame.h"
#include "ListenerCollision.h"
#include "ListenerInputManager.h"
#include "PlayerControls.h"
#include "CameraTarget.h"

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
class Application : public ClassRootSingleton<Application>
{
	private:
		/*!
		* \brief Ogre Root
		*/
		Ogre::Root * root;
		/*!
		* \brief GUI pour afficher les stats
		*/
		Ogre::Overlay * debugOverlay;
		
		/*!
		* \brief Chemin du fichier resources.cfg
		*/
		Ogre::String resourcesCfg;
		/*!
		* \brief Chemin du fichier plugins.cfg
		*/
		Ogre::String pluginsCfg;

		/*!
		* \brief Texte utile pour le debug
		*/
		Ogre::String debugText;
    	/*!
		* \brief Définit si on affiche les stats
		*/
		bool isStatsOn;
    	/*!
		* \brief Définit si on arrête le jeu
		*/
		bool shutDown;
		
    	/*!
		* \brief Identifiant du viewport
		*/
		int idViewport;	
		
	private:
         /*!
         * \brief Permet de terminer le programme
        */
        void killApplication();

	    /*!
		* \brief Permet de recevoir un evènement quand une touche est appuyé
        *   Ici, permet de fermer l'application
		*/	
        void onKeyPressed(Controls::Controls key);
        
        
    public:
        /*!
         * \brief Constructeur
        */
        Application();
        /*!
         * \brief Destructeur
        */
        ~Application();
        
        /*!
         * \brief demarrage du programme
        */
        bool start();
    
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
         * \brief charge la scène
        */
        void initScene();

        /*!
         * \brief mise à jour des statistiques (nb frames...)
        */
        void updateStats(void *);
        
        
        //Getter/Setter
        
		/*!
		* \brief Affiche l'overlay des stats
		* \param show Si on affiche les stats
		*/
		void showDebugOverlay(bool show);
		
		/*!
		* \brief [Getter] Returns a pointer on root
		* \return Get the value of root
		*/
		Ogre::Root * getRoot()
		{
			return this->root;
		}
		
		/*!
		* \brief [Getter] Returns a pointer on debugOverlay
		* \return Get the value of debugOverlay
		*/		
		Ogre::Overlay * getDebugOverlay()
		{
			return this->debugOverlay;
		}
		
		/*!
		* \brief [Setter] Define if the application die
		* \return Set the value of shutdown
		*/	
        void setShutDown(bool shutDown)
        {
            this->shutDown=shutDown;
        }

		/*!
		* \brief [Getter] Returns if the application die
		* \return Get the value of shutdown
		*/	
        bool getShutDown()
        {
            return shutDown;
        }

};

#endif 
