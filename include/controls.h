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
		///Move the target camera at right
		CAM_TARGET_MOVE_RIGHT,
		///Move the target camera at left
		CAM_TARGET_MOVE_LEFT,
		///Move the target camera at up
		CAM_TARGET_MOVE_UP,
		///Move the target camera at down
		CAM_TARGET_MOVE_DOWN,
		///Move the camera at bottom
		CAM_ZOOM_IN,
		///Move the camera at behind
		CAM_ZOOM_OUT,
		///Rotate the camera left
		CAM_ROTATE_LEFT,
		///Rotate right
		CAM_ROTATE_RIGHT,
		///Open the menu
		OPEN_MENU,
		///Select an object
		SELECT,
		///Undo a modification
		UNDO,
		///Add a revision
		ADD_REVISION,
		///Redo a modification
		REDO,
		///Delete an object
		SUPPR,
		///Save the objects
		LOAD,
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
