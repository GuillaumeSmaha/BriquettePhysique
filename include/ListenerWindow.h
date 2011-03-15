/*!
 *  \file  ListenerWindow.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerWindow. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __LISTENER_WINDOW_H__
#define __LISTENER_WINDOW_H__

#include <Ogre.h>
#include "Signal.h"
#include "OISMouse.h"
#include "Application.h"

class Application;


/*!
 * \class ListenerWindow
 * \brief Classe permettant de gérer les événements de la fenêtre.
 */
class ListenerWindow :  public ClassRoot, public Ogre::WindowEventListener
{
	private:
		/*!
		 *  \brief Instance de ListenerWindow pour le singleton
		 */
		static ListenerWindow * _instance ;
		
	public:
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static void createSingleton(Ogre::String windowName);
		/*!
		 *  \brief Retourne un pointeur sur l'instance du singleton
		 */
		static ListenerWindow * getSingletonPtr();
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static ListenerWindow & getSingleton();
        /*!
         * \brief Detruit le singleton
         */
        static void destroySingleton();
	
				
		
	private:
        /*!
		 *  \brief Dispatche un signal lorsque la souris bouge Signal(Ogre::Vector3(X, Y, Z)))
		 */
        Ogre::RenderWindow * renderWindow;		
		
	public:
		/*!
		 * \brief Dispatche un signal lorsque la fenêtre est fermée Signal(void)
		 */
		Signal<void*> signalWindowClosed;
		
	private:
		/*!
		 * \brief Constructor
		 */
		ListenerWindow();
		/*!
		 * \brief Constructor
		 * \param nameWindow Name of the window
		 */
		ListenerWindow(Ogre::String windowName);
		
	public:
		/*!
		 * \brief Destructeur
		 */
		~ListenerWindow();

		/*!
		 *  \brief Action à effectuer pour l'événement "redimensionnement de la fenêtre"
		 * 	\param rw Fenêtre de rendu
		 */
        void windowResized(Ogre::RenderWindow * rw);
		/*!
		 *  \brief Action à effectuer pour l'événement "fermeture de la fenêtre"
		 * 	\param rw Fenêtre de rendu
		 */
        void windowClosed(Ogre::RenderWindow * rw);
        
		//Getter/Setter
		
		/*!
		 * \brief [Getter] Recupère le pointeur
		 * \return Le pointeur sur le capteur d'événements de la fenêtre
		 */
		Ogre::RenderWindow * getRenderWindow()
		{
			return this->renderWindow;
		}
		/*!
		 * \brief [Setter] Définit le pointeur
		 * \return window Le pointeur sur le capteur d'événements de la fenêtre
		 */
		void setRenderWindow(Ogre::RenderWindow * renderWindow)
		{
			this->renderWindow = renderWindow;
		}
};

#endif //__LISTENER_WINDOW_H__
