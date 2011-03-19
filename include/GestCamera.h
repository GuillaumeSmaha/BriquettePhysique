/*!
 *  \file  GestCamera.h
 *  \brief Ce fichier contient la déclaration de la classe GestCamera. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __GEST_CAMERA_H__
#define __GEST_CAMERA_H__

#include <vector>
#include <Ogre.h>
#include "CameraAbstract.h"
#include "CameraFree.h"


/*!
 * \class GestCamera
 * \brief Classe permettant de gérer les viewports.
 */
class GestCamera
{
	private:
		/*!
		 *  \brief Instance de GestCamera pour le singleton
		 */
		static GestCamera * _instance ;
		
	public:
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static void createSingleton();
		/*!
		 *  \brief Retourne un pointeur sur l'instance du singleton
		 */
		static GestCamera * getSingletonPtr();
		/*!
		 *  \brief Retourne une référence sur l'instance du singleton
		 */		
		static GestCamera & getSingleton();
        /*!
         * \brief Detruit le singleton
         */
        static void destroySingleton();
	
				
		
	private:
        /*!
		 *  \brief Vecteur des caméras
		 */
        std::vector<CameraAbstract *> listCameras;
		
	private:
		/*!
		 * \brief Constructor
		 */
		GestCamera();
		
	public:
		/*!
		 * \brief Destructeur
		 */
		~GestCamera();

		
        /*!
		 * \brief Rajoute une caméra à la liste
		 * \param camera Caméra à rajouter à la liste
		 */
        void addCamera(CameraAbstract * camera);
        /*!
		 * \brief Rajoute une caméra à la liste
		 * \param camera Type de caméra à rajouter à la liste
		 * \return Un pointeur sur la caméra créée
		 */
        CameraAbstract * addCamera(CameraAbstract::CameraType cameraType, Ogre::String cameraName);
        /*!
		 * \brief Supprime la caméra de la liste
		 * \param cam Camera à supprimer
		 * \return Si la suppression a réussit
		 */
        bool removeCamera(CameraAbstract * cam);
        /*!
		 * \brief Supprime la caméra de la liste
		 * \param id ID de la caméra à récupérer
		 * \return Si la suppression a réussit
		 */
        bool removeCamera(unsigned int id);
        /*!
		 * \brief Supprime la caméra de la liste
		 * \param id ID de la caméra à récupérer
		 * \return Si la suppression a réussit
		 */
        bool removeCamera(int id)
        {
			return this->removeCamera(static_cast<unsigned int>(id));
		}
        /*!
		 * \brief Récupère l'instance d'une caméra (nonsafe)
		 * \param id ID de la caméra à récupérer
		 * \return Instance de la caméra
		 */
        CameraAbstract * getCamera(unsigned int id);
};

#endif //__GEST_CAMERA_H__
