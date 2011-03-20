/*!
 *  \file  ObjTable.h
 *  \brief Ce fichier contient la déclaration de la classe ObjTable. Gere la table du monde, qui correspond à l'objet statique sur lequelle on pose nos briques.
 */

#ifndef __OBJ_TABLE_H__
#define __OBJ_TABLE_H__

#include <OgreBulletDynamicsRigidBody.h>
#include "OgreBulletCollisionsShape.h"
#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include <Ogre.h>

#include "GestSceneManager.h"
#include "ListenerCollision.h"
class ObjTable
{

public:
    ObjTable();

    ~ObjTable();  


private:
    
    /*
     * \brief l'entité Ogre 
    */
    Ogre::Entity * entTable;
    /*
     * \brief le noeud de l'objet table
    */
    Ogre::SceneNode * tableNode;

    /*
     * \brief La forme de l'objet physique
    */
    OgreBulletCollisions::CollisionShape * shapeTable;
    /*
     * \brief le corps de l'objet physique
    */
    OgreBulletDynamics::RigidBody *bodyTable;


};


#endif//__OBJ_TABLE_H__




