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
		QUIT,
		///Move the camera at right
		CAM_MOVE_RIGHT,
		///Move the camera at left
		CAM_MOVE_LEFT,
		///Move the camera at up
		CAM_MOVE_UP,
		///Move the camera at down
		CAM_MOVE_DOWN,
		///Move the camera at bottom
		CAM_ZOOM_IN,
		///Move the camera at behind
		CAM_ZOOM_OUT,
		///Rotate the camera left
		CAM_ROTATE_LEFT,
		///Rotate right
		CAM_ROTATE_RIGHT,
		///Rotate the camera left
		CAM_ROTATE_UP,
		///Rotate right
		CAM_ROTATE_DOWN,
		///Open the menu
		OPEN_MENU,
		///Switch with the next camera
		SWITCH_NEXT_CAMERA,
		///Switch with the previous camera
		SWITCH_PREV_CAMERA,
		///Select an object
		SELECT,
		///Undo a modification
		UNDO,
		///Redo a modification
		REDO,
		///Delete an object
		SUPPR,
		///Save the objects
		SAVE,
        ///Mouse move to rotate the camera
        MOUSE_CAMERA_ROTATE,
        ///Mouse move to zoom the camera
        MOUSE_CAMERA_ZOOM,
        ///Define if the physic engine (bullet) is started
        SWITCH_BULLET_STATE
	};
}

#endif //__CONTROLS_H__
