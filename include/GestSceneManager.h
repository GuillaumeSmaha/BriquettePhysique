/*!
 *  \file  GestSceneManager.h
 *  \brief Ce fichier contient la déclaration de la classe GestSceneManager. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __GEST_SCENE_MANAGER_H__
#define __GEST_SCENE_MANAGER_H__

#include <Ogre.h>


/*!
 * \class GestSceneManager
 * \brief Classe permettant de gérer les viewports.
 */
class GestSceneManager
{
	private:
		/*!
		 *  \brief Instance de GestSceneManager pour le singleton
		 */
		static GestSceneManager * _instance ;
		
	public:
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static void createSingleton(Ogre::Root * root);
		/*!
		 *  \brief Retourne un pointeur sur l'instance du singleton
		 */
		static GestSceneManager * getSingletonPtr();
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static GestSceneManager & getSingleton();
        /*!
         * \brief Detruit le singleton
         */
        static void destroySingleton();		
		/*!
		* \brief [Getter] Returns a pointer on sceneMgr
		* \return Get the value of sceneMgr
		*/
		static Ogre::SceneManager * getSceneManager();
	
				
		
	private:
		/*!
		*  \brief Scène Manager
		*/
		Ogre::SceneManager * sceneMgr;
		
	private:
		/*!
		 * \brief Constructor
		 */
		GestSceneManager(Ogre::Root * root);
		
	public:
		/*!
		 * \brief Destructeur
		 */
		~GestSceneManager();
};

#endif //__GEST_SCENE_MANAGER_H__
