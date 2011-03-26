/*!
 *  \file  CameraFree.h
 * \brief Ce fichier contient la déclaration de la classe CameraFree. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_FREE_H__
#define __CAMERA_FREE_H__

#include "CameraAbstract.h"
#include "PlayerControls.h"
#include "controls.h"

class GestSceneManager;

/*!
 * \class CameraFree
 * \brief Classe permettant de gérer une caméra libre.
 */
class CameraFree : public CameraAbstract, public ClassRoot
{
	public:
		/*!
		 * \brief Constructeur
		 * \param cameraName Nom de la nouvelle caméra
		 * \param nodeInit Position initiale de la caméra
		 */
		CameraFree(Ogre::String cameraName, Ogre::SceneNode * nodeInit);
		
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void init_camera();
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void update_camera();
        /*!
         * \brief permet de déplacer la caméra lors d'un mouvement de souris
        */
        void onMouseMoved(Ogre::Vector3 mouseVec);
        /*!
         * \brief permet de déplacer la caméra selon les touches utilisés
        */
        void onKeyPressed(Controls::Controls key);

};

#endif //__CAMERA_FREE_H__
