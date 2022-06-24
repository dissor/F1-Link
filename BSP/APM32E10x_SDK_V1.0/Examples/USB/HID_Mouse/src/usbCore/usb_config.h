/*!
 * @file        usb_config.h
 *
 * @brief       USB configuration file    
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */

#ifndef USB_CONFIG_H_
#define USB_CONFIG_H_

#include "HidMouse.h"


#define USB1                        0
#define USB2                        1

/** Select USB peripheral
*   USB1:   Share FIFO with CAN1
*   USB2:   Private FIFO.Not share whith CAN1
*/
#define USB_SELECT                  USB1

/** Configuraion number */
#define USB_CONFIGURATION_NUM       1

/** Endpoint number */
#define USB_EP_NUM                  3

/** Endpoint pack size in bytes */
#define USB_EP_PACKET_SIZE          64

/** Buffer table address */
#define USB_BUFFER_TABLE_ADDR       0

/** EP0 Rx address */
#define USB_EP0_RX_ADDR         (0X18)
/** EP0 Tx address */
#define USB_EP0_TX_ADDR         (0X58)

/** EP1 Tx address */
#define USB_EP1_TX_ADDR         (0X98)

/** EP2 Rx address */
#define USB_EP2_RX_ADDR         (0XD8)

/** Interrupt source */
#define USB_INT_SOURCE          (USBD_INT_RST | USBD_INT_CTR | USBD_INT_SUS | USBD_INT_WKUP)

/** Standard request get configuration user function */
#define USB_UserStdGetConfiguration()
/** Standard request set configuration user function */
#define USB_UserStdSetConfiguraion()                HidMouse_SetConfigCallBack()
/** Standard request get interface user function */
#define USB_UserStdGetInterface()
/** Standard request set interface user function */
#define USB_UserStdSetInterface()
/** Standard request get status user function */
#define USB_UserStdGetStdStatus()
/** Standard request clear feature user function */
#define USB_UserStdClearFeature()
/** Standard request set endpoint feature user function */
#define USB_UserStdSetEndPointFeature()
/** Standard request set device feature user function */
#define USB_UserStdSetDeivceFeature()
/** Standard request set device address user function */
#define USB_UserStdSetDeviceAddr()


#endif
