/*!
 *  \file  CameraAbstract.h
 * \brief Ce fichier contient la déclaration de la classe CameraAbstract. C'est la classe une classe abstraite qui permet d'utiliser différents types de caméras fixes.
 */
#ifndef __CAMERA_ABSTRACT_H__
#define __CAMERA_ABSTRACT_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#endif

#include "ClassRoot.h"
#include "GestSceneManager.h"

/*!
 * \class CameraAbstract
 * \brief Classe abstraite entre le programme principale et la caméra effectivement utilisé. Elle ne peut donc pas être instancié directement
 */
class CameraAbstract : public ClassRoot
{
	public:

		/// Définit les différents types de caméra
		enum CameraType
		{
			/// Caméra Null
			CAMERA_NULL = 0,
			/// Caméra libre
			CAMERA_TARGET = 1
		};
		/// Définit le nombre de caméra
		static const int CameraTypeCount = 1;
		
		
	protected:
		/*!
		 * \brief Type de la caméra
		 */
		CameraAbstract::CameraType cameraType;
		/*!
		 * \brief Camera instanciée
		 */
		Ogre::Camera * camera;
		/*!
		 * \brief Nom de la caméra
		 */
		Ogre::String cameraName;
	
	public:		 
		/*!
		 * \brief Constructeur
		 * \param cameraType Type nouvelle caméra
		 * \param cameraName Nom de la nouvelle caméra
		 */
		CameraAbstract(CameraAbstract::CameraType cameraType, Ogre::String cameraName);
		/*!
		 * \brief Destructeur virtuel
		 */
		 virtual ~CameraAbstract();
		 
		/*!
		 * \brief Initialise la position de la caméra\n
		 * Méthode virtuelle pure à réimplémenter.
		 */
		virtual void init_camera() = 0;
		/*!
		 * \brief Met à jour la position de la caméra\n
		 * Méthode virtuelle pure à réimplémenter.
		 */
		virtual void update_camera() = 0;

		/*!
		 * \brief Direction de la caméra
		 * 	\param x Coordonnée en X
		 * 	\param y Coordonnée en Y
		 * 	\param z Coordonnée en Z
		 */
        virtual void setDirection( Ogre::Real x, Ogre::Real y, Ogre::Real z );
		/*!
		 * \brief Direction de la caméra
		 * 	\param direction Direction
		 */
        virtual void setDirection( Ogre::Vector3 direction );
		/*!
		 * \brief Direction de la caméra
		 * 	\param nodeDirection Direction
		 */
        virtual void setDirection( Ogre::SceneNode * nodeDirection );
		/*!
		 * \brief Position de la caméra
		 * 	\param x Coordonnée en X
		 * 	\param y Coordonnée en Y
		 * 	\param z Coordonnée en Z
		 */
        virtual void setPosition( Ogre::Real x, Ogre::Real y, Ogre::Real z );
		/*!
		 * \brief Position de la caméra
		 * 	\param position Position
		 */
        virtual void setPosition( Ogre::Vector3 position );
        
        
        // Camera Target method
        /*!
         * \brief Retourne le pointeur sue l'attribut 'targetNode'
         * \return Retourne le noeud de la cible
        */
        virtual Ogre::SceneNode * getTargetNode(){return NULL;};
        /*!
         * \brief Définit la cible de la caméra
         * \param vector Vecteur de déplacement
        */
        virtual void definePositionTarget(Ogre::Vector3 vector){};
        
        
        
        
		//Getter/Setter

		/*!
		 * \brief [Getter] Pointeur sur la caméra
		 * \return Le nom de la caméra
		 */
		Ogre::Camera * getCamera()
		{
			return camera;
		}
		/*!
		 * \brief [Getter] Nom de la caméra
		 * \return Le nom de la caméra
		 */
		Ogre::String getCameraName()
		{
			return cameraName;
		}
};

#endif // __CAMERA_ABSTRACT_H__ 
