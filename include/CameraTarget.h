/*!
 *  \file  CameraTarget.h
 * \brief Ce fichier contient la déclaration de la classe CameraTarget. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_TARGET_H__
#define __CAMERA_TARGET_H__

#include "nodeName.h"
#include "CameraAbstract.h"
#include "PlayerControls.h"
#include "controls.h"

class GestSceneManager;

/*!
 * \class CameraTarget
 * \brief Classe permettant de gérer une caméra libre.
 */
class CameraTarget : public CameraAbstract, public ClassRoot
{

    private:
		/*!
		 * \brief Cible de la caméra
		 */
        Ogre::SceneNode * targetNode;
		/*!
		 * \brief Noeud contenant la caméra
		 */
        Ogre::SceneNode * nodeCamera;
        
	public:
		/*!
		 * \brief Constructeur
		 * \param cameraName Nom de la nouvelle caméra
		 * \param targetNode Cible de la caméra
		 */
		CameraTarget(Ogre::String cameraName, Ogre::SceneNode * targetNode = NULL);
		
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void init_camera();
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void update_camera();
        
        /*!
         * \brief Permet de déplacer la caméra lors d'un mouvement de souris
		 * \param mouseVec Vecteur de déplacement de la souris
        */
        void onMouseMoved(Ogre::Vector3 mouseVec);
        /*!
         * \brief Permet de déplacer la caméra selon les touches utilisés
         * \param evt Touche du clavier (Controls::Controls)
        */
        void onKeyPressed(Controls::Controls key);
        /*!
         * \brief Rotation manuelle de la caméra
         * \param angle Angle de rotation
        */
        void manuallyRotate(Ogre::Radian angle);
        /*!
         * \brief Vérifie la rotation de la caméra et met à jour en conséquence
         * \return Vrai si on ne sort pas des limites
        */
        bool checkRotation(Ogre::Real angleRotation);
};

#endif //__CAMERA_TARGET_H__
