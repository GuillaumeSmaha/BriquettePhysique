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

#include "GestSceneManager.h"
#include "ListenerCollision.h"

/*!
* \class ObjBriquette
* \brief Gere une briquette du monde
*/
class ObjBriquette
{
	private:		
		/*!
		 * \brief l'entité Ogre 
		*/
		Ogre::Entity * entBriquette;
        /*!
         * \brief nom de l'entité
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
		 * \brief Permet de créer l'objet physique (avec les propriétés de ogre bullet, une fois que l'objet est positionné
		*/
        void createPhysicalObj(); 

        //###########GETTER / SETTER ############
        
        Ogre::Entity * getEntity()
        {
            return entBriquette;
        }

        Ogre::SceneNode * getSceneNode()
        {
            return briquetteNode;
        }

        void setSceneNode(Ogre::SceneNode * sceneNode)
        {
            briquetteNode=sceneNode;
        }

        OgreBulletCollisions::CollisionShape * getCollisionShape()
        {
            return shapeBriquette;
        }

        OgreBulletDynamics::RigidBody * getRigidBody()
        {
            return bodyBriquette;
        }

};


#endif //__OBJ_BRIQUETTE_H__


