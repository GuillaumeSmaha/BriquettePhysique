/*!
*  \file  Application.h
*  \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
*/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__


#include <Ogre.h>
#include "Utils.h"

#include "PlayerControls.h"
#include "ListenerWindow.h"
#include "ListenerMouse.h"
#include "ListenerKeyboard.h"
#include "ListenerFrame.h"

class ListenerWindow;
class ListenerMouse;
class ListenerKeyboard;
class ListenerFrame;
class PlayerControls;
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
class Application : public ClassRoot
{
	private:
		/*!
		 *  \brief Instance de Application pour le singleton
		 */
		static Application * _instance ;
		
	public:
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static void createSingleton();
		/*!
		 *  \brief Retourne un pointeur sur l'instance du singleton
		 */
		static Application * getSingletonPtr();
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static Application & getSingleton();
        /*!
         * \brief Detruit le singleton
         */
        static void destroySingleton();
	
		
		
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
		*  \brief Capteur d'événements
		*/
		OIS::InputManager * inputManager;
		/*!
		* \brief GUI pour afficher les stats
		*/
		Ogre::Overlay * debugOverlay;
		
		/*!
		*  \brief Chemin du fichier resources.cfg
		*/
		Ogre::String resourcesCfg;
		/*!
		*  \brief Chemin du fichier plugins.cfg
		*/
		Ogre::String pluginsCfg;

		/*!
		* \brief Texte utile pour le debug
		*/
		Ogre::String debugText;
    	/*!
		*  \brief Définit si on affiche les stats
		*/
		bool isStatsOn;
    	/*!
		*  \brief Définit si on arrête le jeu
		*/
		bool shutDown;
		
		
	private:
        /*!
         * \brief Constructeur
        */
        Application();
        
        /*!
         * \brief Reagi aux actions émis par l'utilisateur
         * Ici on regarde simplement si l'on doit quitter l'application
        */
        void onKeyPressed(PlayerControls::Controls key);

         /*!
         * \brief Permet de terminer le programme
        */
        void killApplication();
    public:
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
		* \brief [Getter] Returns a pointer on sceneMgr
		* \return Get the value of sceneMgr
		*/
		Ogre::SceneManager * getSceneManager()
		{
			return this->sceneMgr;
		}
		
		/*!
		* \brief [Getter] Returns a pointer on inputManager
		* \return Get the value of inputManager
		*/
		OIS::InputManager * getInputManager()
		{
			return this->inputManager;
		}
		
		Ogre::Overlay * getDebugOverlay()
		{
			return this->debugOverlay;
		}
        void setShutDown(bool shutDown){
            this->shutDown=shutDown;
        }

        bool getShutDown(){
            return shutDown;
        }

};

#endif 
