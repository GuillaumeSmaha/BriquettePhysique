/*!
 *  \file  GestViewport.h
 * \brief Ce fichier contient la déclaration de la classe GestViewport. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __GEST_VIEWPORT_H__
#define __GEST_VIEWPORT_H__

#include <vector>
#include <Ogre.h>
#include "ClassRootSingleton.h"
#include "ListenerWindow.h"
#include "CameraAbstract.h"


/*!
 * \class GestViewport
 * \brief Classe permettant de gérer les viewports.
 */
class GestViewport : public ClassRootSingleton<GestViewport>
{
	private:
        /*!
		 * \brief Liste des viewports
		 */
		std::vector<Ogre::Viewport *> listViewport;
		
		
	public:
		/*!
		 * \brief Constructor
		 */
		GestViewport();
		/*!
		 * \brief Destructeur
		 */
		~GestViewport();

		
		
		/*!
		 * \brief Ajoute un nouveau viewport
		 * \param gestCamera La caméra correspondant au viewport
		 * \return Id du viewport
		 */
		int addViewport(CameraAbstract * gestCamera);
		/*!
		 * \brief Change la caméra affecté à un viewport
		 * \param idViewport Id du viewport
		 * \param gestCamera La caméra correspondant au viewport
		 * \return Si le changement a réussit
		 */
		bool changeCameraViewport(int idViewport, CameraAbstract * gestCamera);
		/*!
		 * \brief Supprime un viewport
		 * \param idViewport Id du viewport
		 * \return Si la suppression à réussit
		 */
		bool removeViewport(int idViewport);
		
        
		//Getter/Setter

         /*!
		 * \brief Returns the number of viewport
		 * \return Number of viewport
         */
		int countViewport(void)
		{
			return this->listViewport.size();
		}
		/*!
		 * \brief Returns the list of viewport
		 * \return List of viewport
         */
		std::vector<Ogre::Viewport *> getListViewport(void)
		{
			return this->listViewport;
		}	
};

#endif //__GEST_VIEWPORT_H__
