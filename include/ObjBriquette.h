/*!
 *  \file  ObjBriquette.h
 * \brief Ce fichier contient la déclaration de la classe ObjBriquette. Gere une unique briquette, aussi bien son aspect graphique que physique
 */

#ifndef __OBJ_BRIQUETTE_H__
#define __OBJ_BRIQUETTE_H__

#include <Ogre.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include <Utils/OgreBulletConverter.h>
#include <Utils/OgreBulletCollisionsMeshToShapeConverter.h>

#include "collisionBullet.h"
#include "nodeName.h"
#include "GestSceneManager.h"
#include "ListenerCollision.h"
#include "GestObj.h"

class GestObj;

/*!
* \class ObjBriquette
* \brief Gere une briquette du monde
*/
class ObjBriquette
{
	public:
    
		static Ogre::Quaternion defaultOrientation;
		
        /*!
         * \brief permet de mettre a jour la bounding box
        */
        static void updateBtBoundingBox(OgreBulletDynamics::RigidBody * rigidBody);
        
        
	private:		
		/*!
		 * \brief l'entité Ogre 
		*/
		Ogre::Entity * entBriquette;
        /*!
         * \brief Nom de l'entité
         * du type "BriquetteX" avec X un nombre
        */
        Ogre::String nom;
		/*!
		 * \brief le noeud de l'objet briquette
		*/
		Ogre::SceneNode * briquetteNode;
		/*!
		 * \brief La forme de l'objet physique
		*/
		OgreBulletCollisions::CollisionShape * shapeBriquette;
		/*!
		 * \brief le corps de l'objet physique
		*/
		OgreBulletDynamics::RigidBody * bodyBriquette;
		/*!
		 * \brief Indique si la briquette est affiché ou non
		*/
		bool _isDrawing;
		
		
	public:
		/*!
		 * \brief Constructeur: crée un objet briquette intégré au projet et doté d'un comportement physique 
		*/
		ObjBriquette(Ogre::String name);
		/*!
		 * \brief Constructeur de recopie
		*/
		ObjBriquette(const ObjBriquette& briquette);
		/*!
		 * \brief Destructor
		*/
		~ObjBriquette(); 
		
		/*!
		 * \brief Positionne l'objet
		 * \param pos Vecteur position
		*/
		void setPosition(Ogre::Vector3 pos);
		
		/*!
		 * \brief Oriente l'objet
		 * \param orientation Quaternion d'orientation
		*/
		void setOrientation(Ogre::Quaternion orientation);

		/*!
		 * \brief Permet de créer l'objet physique (avec les propriétés de ogre bullet, une fois que l'objet est positionné
		*/
        void createPhysicalObj(); 

		/*!
		 * \brief Permet de supprimer l'objet physique (avec les propriétés de ogre bullet, une fois que l'objet est positionné
		*/
        void removePhysicalObj(); 
        
        

        //###########GETTER / SETTER ############
		
		/*!
		 * \brief Cache la briquette
		*/
		void hide(); 
		/*!
		 * \brief Affiche la briquette
		*/
		void draw(); 
		/*!
		 * \brief Indique si la briquette est affiché
		 * \return Valeur de _isDrawing
		*/
		bool isDrawing(); 
		
        
		/*!
		 * \brief Retourne l'entité de la briquette
		 * \return Valeur de entBriquette
		*/
        Ogre::Entity * getEntity()
        {
            return this->entBriquette;
        }

		/*!
		 * \brief Retourne le noeud contenant la briquette
		 * \return Valeur de briquetteNode
		*/
        Ogre::SceneNode * getSceneNode()
        {
            return this->briquetteNode;
        }

		/*!
		 * \brief Définit le noeud contenant la briquette
		 * \param sceneNode Valeur de briquetteNode
		*/
        void setSceneNode(Ogre::SceneNode * sceneNode)
        {
            this->briquetteNode = sceneNode;
        }

		/*!
		 * \brief Retourne la forme de la bounding box de la briquette
		 * \return Valeur de shapeBriquette
		*/
        OgreBulletCollisions::CollisionShape * getCollisionShape()
        {
            return this->shapeBriquette;
        }

		/*!
		 * \brief Retourne la forme rigide de la briquette
		 * \return Valeur de bodyBriquette
		*/
        OgreBulletDynamics::RigidBody * getRigidBody()
        {
            return this->bodyBriquette;
        }

};


#endif //__OBJ_BRIQUETTE_H__


