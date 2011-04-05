/*!
 *  \file  GestCamera.h
 * \brief Ce fichier contient la déclaration de la classe GestCamera. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __GEST_CAMERA_H__
#define __GEST_CAMERA_H__

#include <vector>
#include <Ogre.h>
#include "ClassRootSingleton.h"
#include "CameraAbstract.h"
#include "CameraTarget.h"


/*!
 * \class GestCamera
 * \brief Classe permettant de gérer les viewports.
 */
class GestCamera : public ClassRootSingleton<GestCamera>
{
	private:
        /*!
		 * \brief Vecteur des caméras
		 */
        std::vector<CameraAbstract *> listCameras;
		
		
	public:
		/*!
		 * \brief Constructor
		 */
		GestCamera();
		/*!
		 * \brief Destructor
		 */
		~GestCamera();

		
        /*!
		 * \brief Rajoute une caméra à la liste
		 * \param camera Caméra à rajouter à la liste
		 */
        void addCamera(CameraAbstract * camera);
        /*!
		 * \brief Rajoute une caméra à la liste
		 * \param cameraType Type de caméra à rajouter à la liste
		 * \param cameraName Nom de la caméra à rajouter
		 * \return Un pointeur sur la caméra créée
		 */
        CameraAbstract * addCamera(CameraAbstract::CameraType cameraType, Ogre::String cameraName, Ogre::SceneNode * targetNode = NULL);
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

        /*
         * \brief recupere la dernière camera placé
        */
        CameraAbstract * getCurrentCamera(){
            return (listCameras.back());
        }
};

#endif //__GEST_CAMERA_H__
