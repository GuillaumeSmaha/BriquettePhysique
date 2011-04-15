/*!
* \file collisionBullet.h
* \brief This file contains the declaration of a enumeration of the collision types
*/
#ifndef __COLLISION_BULLET_H__
#define __COLLISION_BULLET_H__


#define BIT(x) (1<<(x))


enum collisionTypes
{
    COL_NOTHING = 0, //<Collide with nothing
    COL_BRIQUETTE = BIT(1), //<Collide with briquette
    COL_TABLE = BIT(2), //<Collide with table
    COL_RAY = BIT(3), //<Collide with rays (pick up)
    COL_TEST_PLANE = BIT(4) //<Collide with test plane
};


const int BRIQUETTE_COLLIDES_WITH = COL_TABLE | COL_BRIQUETTE | COL_RAY;
const int TABLE_COLLIDES_WITH = COL_NOTHING;
const int RAY_COLLIDES_WITH = COL_BRIQUETTE | COL_TEST_PLANE;
const int TEST_PLANE_COLLIDES_WITH = COL_RAY;


#endif //__COLLISION_BULLET_H__
