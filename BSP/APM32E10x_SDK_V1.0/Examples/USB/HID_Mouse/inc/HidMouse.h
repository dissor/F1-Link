/*!
 * @file        HidMouse.h
 *
 * @brief       HID mouse header file      
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
#ifndef HID_MOUSE_H_
#define HID_MOUSE_H_

/**
 * @brief   Key enumeration
 */
enum
{
    HID_MOUSE_KEY_NULL,
    HID_MOUSE_KEY_LEFT,
    HID_MOUSE_KEY_RIGHT,
    HID_MOUSE_KEY_UP,
    HID_MOUSE_KEY_DOWN,
};

void HidMouse_Init(void);
void HidMouse_Proc(void);
void HidMouse_SetConfigCallBack(void);

#endif
