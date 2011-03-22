/*!
* \file controls.h
* \brief This file contains the declaration of controls key
*/
#ifndef __CONTROLS_H__
#define __CONTROLS_H__

namespace Controls
{
	/// Define the different types of control
	enum Controls
	{
		///None
		NONE = 0,
		///Move the camera at right
		CAM_MOVE_RIGHT = 1,
		///Move the camera at left
		CAM_MOVE_LEFT = 2,
		///Move the camera at up
		CAM_MOVE_UP = 3,
		///Move the camera at down
		CAM_MOVE_DOWN = 4,
		///Move the camera at bottom
		CAM_ZOOM_IN = 5,
		///Move the camera at behind
		CAM_ZOOM_OUT = 6,
		///Open the menu
		OPEN_MENU = 7,
		///Quit the application
		QUIT = 8,
		///Switch with the next camera
		SWITCH_NEXT_CAMERA = 9,
		///Switch with the previous camera
		SWITCH_PREV_CAMERA = 12,
		///Select an object
		SELECT = 12,
		///Undo a modification
		UNDO = 14,
		///Redo a modification
		REDO = 15,
		///Delete an object
		SUPPR = 16,
		///Save the objects
		SAVE = 17
	};
}

#endif //__CONTROLS_H__
