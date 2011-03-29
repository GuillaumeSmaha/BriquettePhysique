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
		///Rotate the camera left
		CAM_ROTATE_LEFT = 7,
		///Rotate right
		CAM_ROTATE_RIGHT = 8,
		///Rotate the camera left
		CAM_ROTATE_UP = 9,
		///Rotate right
		CAM_ROTATE_DOWN = 10,
		///Open the menu
		OPEN_MENU = 11,
		///Quit the application
		QUIT = 12,
		///Switch with the next camera
		SWITCH_NEXT_CAMERA = 13,
		///Switch with the previous camera
		SWITCH_PREV_CAMERA = 14,
		///Select an object
		SELECT = 15,
		///Undo a modification
		UNDO = 16,
		///Redo a modification
		REDO = 17,
		///Delete an object
		SUPPR = 18,
		///Save the objects
		SAVE = 19,
        ///by default, we have a cursor which allow to select a briquette, when we change the mod, we move the view
        CHANGE_MOUSE_MOD=20
	};
}

#endif //__CONTROLS_H__
