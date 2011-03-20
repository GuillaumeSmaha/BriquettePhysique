/*!
 *  \file  ObjBriquette.h
 *  \brief Ce fichier contient la déclaration de la classe ObjBriquette. Gere une unique briquette, aussi bien son aspect graphique que physique
 */

#ifndef __OBJ_BRIQUETTE_H__
#define __OBJ_BRIQUETTE_H__

#include <OgreBulletDynamicsRigidBody.h>
#include "OgreBulletCollisionsShape.h"
#include <Shapes/OgreBulletCollisionsBoxShape.h>
#include <Ogre.h>

#include "GestSceneManager.h"
#include "ListenerCollision.h"


class ObjBriquette
{

public:

    /*!
     * Constructeur: crée un objet table intégré au projet et doté d'un comportement physique 
    */
    ObjBriquette();

    ~ObjBriquette();  


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


#endif//__OBJ_BRIQUETTE_H__


