/*!
 *  \file  ObjTable.h
 * \brief Ce fichier contient la déclaration de la classe ObjTable. Gere la table du monde, qui correspond à l'objet statique sur lequelle on pose nos briques.
 */

#ifndef __OBJ_TABLE_H__
#define __OBJ_TABLE_H__

#include <Ogre.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletCollisionsShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "collisionBullet.h"
#include "GestSceneManager.h"
#include "ListenerCollision.h"

/*!
* \class ObjTable
* \brief Gere la table du monde, qui correspond à l'objet statique sur lequelle on pose nos briques.
*/
class ObjTable
{
	private:		
		/*!
		 * \brief l'entité Ogre 
		*/
		Ogre::Entity * entTable;
		/*!
		 * \brief le noeud de l'objet table
		*/
		Ogre::SceneNode * tableNode;

		/*!
		 * \brief La forme de l'objet physique
		*/
		OgreBulletCollisions::CollisionShape * shapeTable;
		/*!
		 * \brief le corps de l'objet physique
		*/
		OgreBulletDynamics::RigidBody * bodyTable;
		
		
	public:
		/*!
		 * Constructeur: crée un objet table intégré au projet et doté d'un comportement physique 
		*/
		ObjTable(Ogre::Real size = 100.0, Ogre::Real depth = 0.0);
		/*!
		 * Destructeur: permet de nettoyer les objs alloués
		*/
		~ObjTable(); 


        // ################################################# GETTER-SETTER #############
        
        
        /*!
         * \brief [Getter] Permet de récuperer l'entité
         * \return Un pointeur sur l'objet entTable
        */
        Ogre::Entity * getEntity()
        {
            return this->entTable;
        }

        /*!
         * \brief [Getter] Permet de récuperer le noeud contenant la table
         * \return Un pointeur sur l'objet tableNode
        */
        Ogre::SceneNode * getNode()
        {
            return this->tableNode;
        }
};


#endif//__OBJ_TABLE_H__




