/*!
 *  \file  ListenerMouse.h
 * \brief Ce fichier contient la déclaration de la classe ListenerKeyboard. C'est la classe gérant les événements de la souris.
 */
#ifndef __LISTENER_MOUSE_H__
#define __LISTENER_MOUSE_H__

#include <OISMouse.h>
#include "ClassRootSingleton.h"
#include "Signal.h"
#include "ListenerInputManager.h"


/*!
 * \class ListenerMouse
 * \brief Classe permettant de gérer les événements de la souris.
 */
class ListenerMouse : public ClassRootSingleton<ListenerMouse>, public OIS::MouseListener 
{
	public:
		/*!
		 * \brief Créé le singleton
		 */		
		static void createSingleton();
		
	private:
		/*!
		 * \brief Capteur d'événements de la souris
		 */
        OIS::Mouse * mouse;

	public:
        /*!
		 * \brief Dispatche un signal lorsque la souris bouge Signal(Ogre::Vector3(X, Y, Z)))
		 */
        Signal<Ogre::Vector3> signalMouseMoved;
        /*!
		 * \brief Dispatche un signal lorsque une touche de la souris est enfoncée Signal(OIS::MouseButtonID)
		 */
        Signal<OIS::MouseButtonID> signalMousePressed;
        /*!
		 * \brief Dispatche un signal lorsque une touche de la souris est relâchée Signal(OIS::MouseButtonID)
		 */
        Signal<OIS::MouseButtonID> signalMouseReleased;
        
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerMouse();
		/*!
		 * \brief Destructeur
		 */
		~ListenerMouse();
		
		/*!
		 * \brief Recupère les événements
		 */
		void capture();
		/*!
		 * \brief Recupère les événements
		 */
		void capture(void *);
		/*!
		 * \brief Action à effectuer pour l'événement "souis en mouvement"
		 * \param evt Evenement de la souris
		 * \return Si il y a une erreur durant l'événement
		 */
        bool mouseMoved( const OIS::MouseEvent &evt );
		/*!
		 * \brief Action à effectuer pour l'événement "touche de la souris cliquée"
		 * \param evt Evenement de la souris
		 * \param id Identifiant du bouton de la souris
		 * \return Si il y a une erreur durant l'événement
		 */
        bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
		/*!
		 * \brief Action à effectuer pour l'événement "touche de la souris relachée"
		 * \param evt Evenement de la souris
		 * \param id Identifiant du bouton de la souris
		 * \return Si il y a une erreur durant l'événement
		 */
        bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
        
        
        //Getter/Setter

		/*!
		 * \brief [Getter] Récupère la valeur de mouse
		 * \return Le pointeur sur le capteur d'événements de la souris
		 */
		OIS::Mouse * getMouse()
		{
			return this->mouse;
		}
};

#endif //__LISTENER_MOUSE_H__
