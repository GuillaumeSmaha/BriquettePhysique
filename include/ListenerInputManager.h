/*!
 *  \file  ListenerInputManager.h
 * \brief Ce fichier contient la déclaration de la classe ListenerInputManager. C'est la classe gérant les événements du clavier.
 */
#ifndef __LISTENER_INPUT_MANAGER_H__
#define __LISTENER_INPUT_MANAGER_H__

#include <OISInputManager.h>
#include "ClassRootSingleton.h"
#include "ListenerWindow.h"


/*!
 * \class ListenerInputManager
 * \brief Classe permettant de gérer les événements du clavier.
 */
class ListenerInputManager : public ClassRootSingleton<ListenerInputManager>
{			
	public:
		/*!
		 * \brief Créé le singleton
		 */		
		static void createSingleton();
		
	private:
		/*!
		 * \brief Gestionnaire d'entrées
		 */
        OIS::InputManager * inputManager;
                
        
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerInputManager();
		/*!
		 * \brief Destructeur
		 */
		~ListenerInputManager();

        
        //Getter/Setter

		/*!
		* \brief [Getter] Returns a pointer on inputManager
		* \return Get the value of inputManager
		*/
		OIS::InputManager * getInputManager()
		{
			return this->inputManager;
		}
};

#endif //__LISTENER_INPUT_MANAGER_H__
