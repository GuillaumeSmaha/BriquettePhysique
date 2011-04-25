/*!
* \file mouseMove.h
* \brief This file contains the declaration of a structure for mouse dragging
*/
#ifndef __MOUSE_MOVE_H__
#define __MOUSE_MOVE_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#include <OISMouse.h>
#endif

#include "controls.h"

/// Define a structure contening the mouse button id or player control button and the vector of the mouse mouse
struct MouseMove_t
{
	///Mouse button id
	OIS::MouseButtonID mouseId;
	
	///Player control mouse id
	Controls::Controls controlMouseId;
		
	///Vector
	Ogre::Vector3 vector;
};


#endif //__MOUSE_MOVE_H__
