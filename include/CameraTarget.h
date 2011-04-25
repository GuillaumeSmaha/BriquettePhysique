/*!
 *  \file  CameraTarget.h
 * \brief Ce fichier contient la déclaration de la classe CameraTarget. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_TARGET_H__
#define __CAMERA_TARGET_H__

#include "nodeName.h"
#include "mouseMove.h"
#include "CameraAbstract.h"
#include "PlayerControls.h"
#include "controls.h"

class GestSceneManager;

/*!
 * \class CameraTarget
 * \brief Classe permettant de gérer une caméra libre.
 */
class CameraTarget : public CameraAbstract
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
		 * \brief Destructeur
		 */
		~CameraTarget();
		
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
		 * \param mouseMove Structure de déplacement de la souris
        */
        void onMouseMoved(MouseMove_t &mouseMove);
        /*!
         * \brief Permet de déplacer la caméra selon les touches utilisés
         * \param key Touche du clavier (Controls::Controls)
        */
        void onKeyPressed(Controls::Controls key);
        /*!
         * \brief Rotation manuelle de la caméra
         * \param angle Angle de rotation
        */
        void manuallyRotate(Ogre::Radian angle);
        /*!
         * \brief Effectue un zoom
         * \param zoomDist Zoom à effectuer
        */
        void zoom(Ogre::Real zoomDist);
        /*!
         * \brief Déplace la cible de la caméra
         * \param vector Vecteur de déplacement
        */
        void moveTarget(Ogre::Vector3 vector);
        /*!
         * \brief Vérifie la rotation de la caméra et met à jour en conséquence
         * \return Vrai si on ne sort pas des limites
        */
        bool checkRotation(Ogre::Degree yaw, Ogre::Degree pitch);
};

#endif //__CAMERA_TARGET_H__
