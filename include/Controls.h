#ifndef __CONTROLS_H__
#define __CONTROLS_H__




/// Définit les différents types de contrôles
namespace Controls{
enum Controls
{
    NONE = 0,
    CAM_MOVE_RIGHT= 1,
    CAM_MOVE_LEFT= 2,
    CAM_MOVE_UP= 3,
    CAM_MOVE_DOWN= 4,
    CAM_ZOOM_IN= 5,
    CAM_ZOOM_OUT= 6,
    OPEN_MENU= 7,
    QUIT = 8,
    SWITCH_NEXT_CAMERA = 9,
    SWITCH_PREV_CAMERA = 12,
    SELECT = 12,    //permet de sélectionner une briquette
    UNDO = 14,
    SUPPR = 15,
    SAVE= 16
};
}

#endif //__CONTROLS_H__
