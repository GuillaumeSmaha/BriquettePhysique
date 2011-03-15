/*!
 *  \file  ListenerKeyboard.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerKeyboard. C'est la classe gérant les événements du clavier.
 */
#ifndef __LISTENER_KEYBOARD_H__
#define __LISTENER_KEYBOARD_H__

#include <Ogre.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include "ClassRoot.h"
#include "Signal.h"

/*!
 * \class ListenerKeyboard
 * \brief Classe permettant de gérer les événements du clavier.
 */
class ListenerKeyboard : public ClassRoot , public OIS::KeyListener
{
	private:
		/*!
		 *  \brief Instance de ListenerKeyboard pour le singleton
		 */
		static ListenerKeyboard * _instance ;
		
	public:
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static void createSingleton(OIS::InputManager * inputManager);
		/*!
		 *  \brief Retourne un pointeur sur l'instance du singleton
		 */
		static ListenerKeyboard * getSingletonPtr();
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static ListenerKeyboard & getSingleton();
		
		
		
		
	private:
        /*!
		 *  \brief Gestionnaire d'événements I/O
		 */
        OIS::InputManager * inputManager;
		/*!
		 *  \brief Capteur d'événements du clavier
		 */
        OIS::Keyboard * keyboard;

	public:
        /*!
         * \brief Dispatche un signal lorsqu'une touche du clavier est préssée Signal(const OIS::KeyEvent &evt)
         */
        Signal<const OIS::KeyEvent&> signalKeyPressed;
        /*!
         * \brief Dispatche un signal lorsqu'une touche du clavier est relâchée Signal(const OIS::KeyEvent &evt)
         */
        Signal<const OIS::KeyEvent&> signalKeyReleased;
                
        
	private:
		/*!
		 * \brief Constructeur
		 * \param inputManager Gestionnaire d'entrée
		 */
		ListenerKeyboard(OIS::InputManager * inputManager);
		
	public:
		/*!
		 * \brief Destructeur
		 */
		~ListenerKeyboard();

		/*!
		 * \brief Recupère les événements
		 */
		void capture();
		/*!
		 * \brief Recupère les événements
		 */
		void capture(void *);

		/*!
		 * \brief Action à effectuer pour l'événement "touche pressée"
		 * \param evt Evenement du clavier
		 * \return Si il y a une erreur durant l'événement
		 */
        bool keyPressed( const OIS::KeyEvent &evt );
		/*!
		 * \brief Action à effectuer pour l'événement "touche relachée"
		 * \param evt Evenement du clavier
		 * \return Si il y a une erreur durant l'événement
		 */
        bool keyReleased( const OIS::KeyEvent &evt );
        
        //Getter/Setter

		/*!
		 * \brief [Getter] Recupère la valeur de keyboard
		 * \return Le pointeur sur le capteur d'événements du clavier
		 */
		OIS::Keyboard * getKeyboard()
		{
			return this->keyboard;
		}
};

#endif //__LISTENER_KEYBOARD_H__
