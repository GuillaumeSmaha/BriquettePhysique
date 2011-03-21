/*!
 *  \file  ListenerWindow.h
 * \brief Ce fichier contient la déclaration de la classe ListenerWindow. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __LISTENER_WINDOW_H__
#define __LISTENER_WINDOW_H__

#include <Ogre.h>
#include "ClassRootSingleton.h"
#include "Signal.h"
#include "OISMouse.h"
#include "Application.h"

class Application;


/*!
 * \class ListenerWindow
 * \brief Classe permettant de gérer les événements de la fenêtre.
 */
class ListenerWindow :  public ClassRootSingleton<ListenerWindow>, public Ogre::WindowEventListener
{
	public:
		/*!
		 * \brief Créé le singleton
		 */		
		static void createSingleton();
		/*!
		 * \brief Créé le singleton
		 * \param windowName Name of the window
		 */		
		static void createSingleton(Ogre::String windowName);
		
		
	private:
        /*!
		 * \brief Dispatche un signal lorsque la souris bouge Signal(Ogre::Vector3(X, Y, Z)))
		 */
        Ogre::RenderWindow * renderWindow;		
		
	public:
		/*!
		 * \brief Dispatche un signal lorsque la fenêtre est fermée Signal(void)
		 */
		Signal<void*> signalWindowClosed;
		
	public:
		/*!
		 * \brief Constructor
		 * \param windowName Name of the window
		 */
		ListenerWindow(Ogre::String windowName);
		/*!
		 * \brief Destructeur
		 */
		~ListenerWindow();

		/*!
		 * \brief Action à effectuer pour l'événement "redimensionnement de la fenêtre"
		 * 	\param rw Fenêtre de rendu
		 */
        void windowResized(Ogre::RenderWindow * rw);
		/*!
		 * \brief Action à effectuer pour l'événement "fermeture de la fenêtre"
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
