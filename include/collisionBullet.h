/*!
* \file collisionBullet.h
* \brief This file contains the declaration of a enumeration of the collision types
*/
#ifndef __COLLISION_BULLET_H__
#define __COLLISION_BULLET_H__

#include <BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>


#define BIT(x) (1<<(x))


enum collisionTypes
{
    COL_NOTHING		= 0,		// Collide with nothing
    COL_BRIQUETTE	= BIT(7),	// Collide with briquette
    COL_TABLE		= BIT(8),	// Collide with table
    COL_RAY			= BIT(9),	// Collide with rays (pick up)
    COL_TEST_PLANE	= BIT(10)	// Collide with test plane
};

const int BRIQUETTE_COLLIDES_WITH		= btBroadphaseProxy::DefaultFilter | btBroadphaseProxy::StaticFilter | COL_BRIQUETTE | COL_TABLE | COL_RAY;
const int TABLE_COLLIDES_WITH			= btBroadphaseProxy::DefaultFilter | btBroadphaseProxy::StaticFilter | COL_BRIQUETTE;
const int RAY_COLLIDES_WITH				= btBroadphaseProxy::DefaultFilter | btBroadphaseProxy::StaticFilter | COL_BRIQUETTE | COL_TEST_PLANE;
const int TEST_PLANE_COLLIDES_WITH		= btBroadphaseProxy::DefaultFilter | btBroadphaseProxy::StaticFilter | COL_RAY;


#endif //__COLLISION_BULLET_H__
