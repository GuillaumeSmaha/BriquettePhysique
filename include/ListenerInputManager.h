/*!
 *  \file  ListenerInputManager.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerInputManager. C'est la classe gérant les événements du clavier.
 */
#ifndef __LISTENER_INPUT_MANAGER_H__
#define __LISTENER_INPUT_MANAGER_H__

#include <OISInputManager.h>
#include "ListenerWindow.h"


/*!
 * \class ListenerInputManager
 * \brief Classe permettant de gérer les événements du clavier.
 */
class ListenerInputManager : public ClassRoot
{
	private:
		/*!
		 *  \brief Instance de ListenerInputManager pour le singleton
		 */
		static ListenerInputManager * _instance ;
		
	public:
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static void createSingleton();
		/*!
		 *  \brief Retourne un pointeur sur l'instance du singleton
		 */
		static ListenerInputManager * getSingletonPtr();
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static ListenerInputManager & getSingleton();
        /*!
         * \brief Detruit le singleton
         */
        static void destroySingleton();
		
			
	private:
		/*!
		 *  \brief Gestionnaire d'entrées
		 */
        OIS::InputManager * inputManager;
                
        
	private:
		/*!
		 * \brief Constructeur
		 * \param inputManager Gestionnaire d'entrée
		 */
		ListenerInputManager();
		
	public:
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
