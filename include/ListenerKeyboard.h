/*!
 *  \file  ListenerKeyboard.h
 * \brief Ce fichier contient la déclaration de la classe ListenerKeyboard. C'est la classe gérant les événements du clavier.
 */
#ifndef __LISTENER_KEYBOARD_H__
#define __LISTENER_KEYBOARD_H__

#include <OISKeyboard.h>
#include "ClassRootSingleton.h"
#include "Signal.h"
#include "ListenerInputManager.h"


/*!
 * \class ListenerKeyboard
 * \brief Classe permettant de gérer les événements du clavier.
 */
class ListenerKeyboard : public ClassRootSingleton<ListenerKeyboard> , public OIS::KeyListener
{
	public:
		/*!
		 * \brief Créé le singleton
		 */		
		static void createSingleton();
		
	private:
		/*!
		 * \brief Capteur d'événements du clavier
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
                
       
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerKeyboard();
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
