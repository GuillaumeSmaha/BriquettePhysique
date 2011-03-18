/*!
*  \file  Application.h
*  \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
*/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__


#include <Ogre.h>
#include "Utils.h"
#include "PlayerControls.h"
#include "GestSceneManager.h"
#include "ListenerWindow.h"
#include "ListenerFrame.h"
#include "ListenerCollision.h"
#include "ListenerInputManager.h"

class ListenerWindow;
class ListenerFrame;

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
		* \brief [Getter] Returns a pointer on debugOverlay
		* \return Get the value of debugOverlay
		*/		
		Ogre::Overlay * getDebugOverlay()
		{
			return this->debugOverlay;
		}
		
        void setShutDown(bool shutDown)
        {
            this->shutDown=shutDown;
        }

        bool getShutDown()
        {
            return shutDown;
        }

};

#endif 
