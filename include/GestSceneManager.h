/*!
 *  \file  GestSceneManager.h
 * \brief Ce fichier contient la déclaration de la classe GestSceneManager. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __GEST_SCENE_MANAGER_H__
#define __GEST_SCENE_MANAGER_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#endif

#include "ClassRootSingleton.h"


/*!
 * \class GestSceneManager
 * \brief Classe permettant de gérer les viewports.
 */
class GestSceneManager : public ClassRootSingleton<GestSceneManager>
{
	public:
		/*!
		 * \brief Créé le singleton
		 */		
		static void createSingleton();
		/*!
		 * \brief Créé le singleton
		 * \param root Racine d'Ogre
		 */		
		static void createSingleton(Ogre::Root * root);
		/*!
		* \brief [Getter] Returns a pointer on sceneMgr
		* \return Get the value of sceneMgr
		*/
		static Ogre::SceneManager * getSceneManager();
	
    public:

        /*!
         * \brief Permet de créer une nouvelle entité
        */
        Ogre::Entity * createEntity(const Ogre::String &name, const Ogre::String meshName);

		
	private:
		/*!
		* \brief Scène Manager
		*/
		Ogre::SceneManager * sceneMgr;
		
		
	public:
		/*!
		 * \brief Constructor
		 */
		GestSceneManager(Ogre::Root * root);
		/*!
		 * \brief Destructeur
		 */
		~GestSceneManager();
};

#endif //__GEST_SCENE_MANAGER_H__
