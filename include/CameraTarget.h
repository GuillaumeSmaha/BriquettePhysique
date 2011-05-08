/*!
 *  \file  CameraTarget.h
 * \brief Ce fichier contient la déclaration de la classe CameraTarget. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_TARGET_H__
#define __CAMERA_TARGET_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#include <OgreBulletCollisions.h>
#include <OgreBulletDynamics.h>
#include <OgreBulletCollisionsShape.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsPreRequisites.h>
#endif

#include "controls.h"
#include "nodeName.h"
#include "mouseMove.h"
#include "CameraAbstract.h"
#include "PlayerControls.h"
#include "GestSceneManager.h"
#include "ListenerFrame.h"


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
        
		/*!
		 * \brief Position de la cible de la caméra
		 */
        Ogre::Vector3 targetPosition;
        
		/*!
		 * \brief Touche restée appuyée pour le deplacement de la cible en X
		 */
        Controls::Controls keyPressedMoveTargetX;
		/*!
		 * \brief Touche restée appuyée pour le deplacement de la cible en Y
		 */
        Controls::Controls keyPressedMoveTargetY;
        
        
	public:
		/*!
		 * \brief Constructeur
		 * \param cameraType Type nouvelle caméra
		 * \param cameraName Nom de la nouvelle caméra
		 * \param targetNode Cible de la caméra
		 */
		CameraTarget(CameraAbstract::CameraType cameraType, Ogre::String cameraName, Ogre::SceneNode * targetNode = NULL);
		/*!
		 * \brief Destructeur
		 */
		~CameraTarget();
		
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void init_camera();
		/*!
		 * \brief Met à jour la position de la caméra
		 */
		void update_camera();
		
		/*!
		 * \brief Met à jour la position de la caméra
		 * \param null NULL
		 */
		void update_camera(void * null);
        
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
         * \brief Permet de déplacer la caméra selon les touches utilisés
         * \param key Touche du clavier (Controls::Controls)
        */
        void onKeyReleased(Controls::Controls key);
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
         * \brief Définit la cible de la caméra
         * \param vector Vecteur de déplacement
        */
        void definePositionTarget(Ogre::Vector3 vector);
     
	private:
        /*!
         * \brief Vérifie la rotation de la caméra et met à jour en conséquence
         * \return Vrai si on ne sort pas des limites
        */
        bool checkRotation(Ogre::Degree yaw, Ogre::Degree pitch);
        /*!
         * \brief Déplace la position de la cible de la caméra
         * \param vector Vecteur de position
        */
        void moveTarget(Ogre::Vector3 vector);
        
        
        
        // Getter - Setter
        
	public:
        /*!
         * \brief Retourne la valeur de l'attribut keyPressedMoveTargetX
         * \return La valeur de keyPressedMoveTargetX
        */
        Controls::Controls getKeyPressedMoveTargetX();
        /*!
         * \brief Définit la valeur de l'attribut keyPressedMoveTargetX
         * \param keyPressedMoveTargetX Valeur à attribuer
        */
        void setKeyPressedMoveTargetX(Controls::Controls keyPressedMoveTargetX);
        
        /*!
         * \brief Retourne la valeur de l'attribut keyPressedMoveTargetY
         * \return La valeur de keyPressedMoveTargetY
        */
        Controls::Controls getKeyPressedMoveTargetY();
        /*!
         * \brief Définit la valeur de l'attribut keyPressedMoveTargetY
         * \param keyPressedMoveTargetY Valeur à attribuer
        */
        void setKeyPressedMoveTargetY(Controls::Controls keyPressedMoveTargetY);
        /*!
         * \brief Retourne le pointeur sue l'attribut 'targetNode'
         * \return Retourne le noeud de la cible
        */
        Ogre::SceneNode * getTargetNode();
        
};

#endif //__CAMERA_TARGET_H__
