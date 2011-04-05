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
		///None (Don't delete !!!)
		NONE = 0,
		///Quit the application
		QUIT = 1,
		///Move the camera at right
		CAM_MOVE_RIGHT = 2,
		///Move the camera at left
		CAM_MOVE_LEFT = 3,
		///Move the camera at up
		CAM_MOVE_UP = 4,
		///Move the camera at down
		CAM_MOVE_DOWN = 5,
		///Move the camera at bottom
		CAM_ZOOM_IN = 6,
		///Move the camera at behind
		CAM_ZOOM_OUT = 7,
		///Rotate the camera left
		CAM_ROTATE_LEFT = 8,
		///Rotate right
		CAM_ROTATE_RIGHT = 9,
		///Rotate the camera left
		CAM_ROTATE_UP = 10,
		///Rotate right
		CAM_ROTATE_DOWN = 11,
		///Open the menu
		OPEN_MENU = 12,
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
        ///Mouse move to rotate the camera
        MOUSE_CAMERA_ROTATE = 20,
        ///Mouse move to zoom the camera
        MOUSE_CAMERA_ZOOM = 21,
        ///Define if the physic engine (bullet) is started
        SWITCH_BULLET_STATE = 22
	};
}

#endif //__CONTROLS_H__
