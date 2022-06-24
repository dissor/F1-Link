/*!
 * @file        HidMouse.c
 *
 * @brief       HID Mouse source file        
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
#include "HidMouse.h"
#include "HidMouse_descriptor.h"
#include "usb.h"
#include "apm32e10x_eint.h"
#include "apm32e10x_gpio.h"
#include "apm32e10x_rcm.h"
#include "apm32e10x_misc.h"
#include <string.h>

/** Device descriptor */
static const USB_Descriptor_T s_deviceDescriptor = {g_hidMouseDeviceDescriptor, HID_MOUSE_DEVICE_DESCRIPTOR_SIZE};
/** Config descriptor */
static const USB_Descriptor_T s_configDescriptor = {g_hidMouseConfigDescriptor, HID_MOUSE_CONFIG_DESCRIPTOR_SIZE};
/** String descriptor */
static const USB_Descriptor_T s_stringDescriptor[] = 
{
    {g_hidMouseLandIDString, HID_MOUSE_LANGID_STRING_SIZE},
    {g_hidMouseVendorString, HID_MOUSE_VENDOR_STRING_SIZE},
    {g_hidMouseProductString, HID_MOUSE_PRODUCT_STRING_SIZE},
    {g_hidMouseSerialString, HID_MOUSE_SERIAL_STRING_SIZE}
};

/** Endpoint status */
static uint8_t s_statusEP = 1;
/** USB configuration status */
static uint8_t s_usbConfigStatus = 0;

/*!
 * @brief       Reset
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void HidMouse_Reset(void)
{
    uint8_t i;

    s_usbConfigStatus = 0;
    
    USBD_SetBufferTable(USB_BUFFER_TABLE_ADDR);

    USBD_SetEPType(USBD_EP_0, USBD_EP_TYPE_CONTROL);
    USBD_SetEPTxStatus(USBD_EP_0, USBD_EP_STATUS_STALL);
    USBD_SetEPTxAddr(USBD_EP_0, USB_EP0_TX_ADDR);
    USBD_SetEPRxAddr(USBD_EP_0, USB_EP0_RX_ADDR);
    USBD_ResetEPKind(USBD_EP_0);
    USBD_SetEPRxCnt(USBD_EP_0, USB_EP_PACKET_SIZE);
    USBD_SetEPRxStatus(USBD_EP_0, USBD_EP_STATUS_VALID);

    USBD_SetEPType(USBD_EP_1, USBD_EP_TYPE_INTERRUPT);
    USBD_SetEPTxAddr(USBD_EP_1, USB_EP1_TX_ADDR);
    USBD_SetEPTxCnt(USBD_EP_1, 4);
    USBD_SetEPRxTxStatus(USBD_EP_1, USBD_EP_STATUS_NAK, USBD_EP_STATUS_DISABLE);
    
    for(i = 0; i < USB_EP_NUM; i++)
    {
        USBD_SetEpAddr((USBD_EP_T)i, i);
    }
    
    USBD_SetDeviceAddr(0);
    USBD_Enable();
}

/*!
 * @brief       Endpoint handler
 *
 * @param       ep:     Endpoint number
 *
 * @param       dir:    Direction.0: Out; 1: In
 *
 * @retval      None
 *
 * @note       
 */
void HidMouse_EPHandler(uint8_t ep, uint8_t dir)
{
    s_statusEP = 1;
}

/*!
 * @brief       Standard request set configuration call back
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void HidMouse_SetConfigCallBack(void)
{
    s_usbConfigStatus = 1;
}

/*!
 * @brief       GPIO init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void HidMouse_GPIOInit(void)
{
    GPIO_Config_T gpioConfigStruct;
    
    
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    
    gpioConfigStruct.mode = GPIO_MODE_IN_PU;
    gpioConfigStruct.pin = GPIO_PIN_0 | GPIO_PIN_1;
    gpioConfigStruct.speed = GPIO_SPEED_50MHz;
    
    GPIO_Config(GPIOA, &gpioConfigStruct);
}

/*!
 * @brief       Mouse write
 *
 * @param       key:    Mouse key
 *
 * @retval      None
 *
 * @note       
 */
void HidMouse_Write(uint8_t key)
{
    int8_t x = 0;
    int8_t y = 0;
    uint8_t buffer[4] = {0, 0, 0, 0};
  
    switch (key)
    {
        case HID_MOUSE_KEY_LEFT:
            x -= 10;
        break;
        
        case HID_MOUSE_KEY_RIGHT:
            x += 10;
        break;
        
        case HID_MOUSE_KEY_UP:
            y -= 10;
        break;
        
        case HID_MOUSE_KEY_DOWN:
            y += 10;
        break;
        
        default:
            return;
    }

    buffer[1] = x;
    buffer[2] = y;

    s_statusEP = 0;
    
    USBD_WriteDataToEP(USBD_EP_1, buffer, sizeof(buffer));
    
    USBD_SetEPTxStatus(USBD_EP_1, USBD_EP_STATUS_VALID);
}

/*!
 * @brief       Standard request Report HID Descriptor
 *
 * @param       reqData:    Standard request data
 *
 * @retval      None
 *
 * @note       
 */
void HidMouse_ReportDescriptor(USB_DevReqData_T *reqData)
{
    uint8_t len;
    
    if((reqData->bRequest == USB_GET_DESCRIPTOR) && 
        (reqData->bmRequestType.bit.recipient == USB_RECIPIENT_INTERFACE) && 
        (reqData->bmRequestType.bit.type == USB_REQ_TYPE_STANDARD))
    {
        if(reqData->wValue[1] == 0x21)
        {
            len = USB_MIN(reqData->wLength[0], 9);
            USB_CtrlInData((uint8_t *)&g_hidMouseConfigDescriptor[0x12], len);
        }
        else if(reqData->wValue[1] == 0x22)
        {
            len = USB_MIN(reqData->wLength[0], HID_MOUSE_REPORT_DESCRIPTOR_SIZE);
            USB_CtrlInData((uint8_t *)g_hidMouseReportDescriptor, len);
        }
    }
    else
    {
        USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
    }
}

/*!
 * @brief       Read key 
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
uint8_t HidMouse_ReadKey(void)
{
    /** Right key */
    if(!GPIO_ReadInputBit(GPIOA, GPIO_PIN_0))
    {
        return HID_MOUSE_KEY_RIGHT;
    }
   
    /** Left key */
    if(!GPIO_ReadInputBit(GPIOA, GPIO_PIN_1))
    {
        return HID_MOUSE_KEY_LEFT;
    }    

    return HID_MOUSE_KEY_NULL;
}

/*!
 * @brief       Mouse process
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void HidMouse_Proc(void)
{
    uint8_t key = HID_MOUSE_KEY_NULL;

    if(!s_usbConfigStatus)
    {
        return;
    }
    
    key = HidMouse_ReadKey();
    if(key != HID_MOUSE_KEY_NULL)
    {
        if(s_statusEP)
        {
            HidMouse_Write(key);
        }
    }
}

/*!
 * @brief       Interrupt init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void HidMouse_IntInit(void)
{
    EINT_Config_T EINT_ConfigStruct;
    
    EINT_ConfigStruct.mode = EINT_MODE_INTERRUPT;
    EINT_ConfigStruct.line = EINT_LINE_18;
    EINT_ConfigStruct.trigger = EINT_TRIGGER_RISING;
    EINT_ConfigStruct.lineCmd = ENABLE;
    EINT_Config(&EINT_ConfigStruct);
    
#if USB_SELECT == USB1
    NVIC_EnableIRQRequest(USBD1_LP_CAN1_RX0_IRQn, 2, 0);  
#else
    NVIC_EnableIRQRequest(USB2_LP_IRQn, 2, 0);
#endif    

    NVIC_EnableIRQRequest(USBDWakeUp_IRQn, 1, 0);     
}

/*!
 * @brief       HID mouse init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void HidMouse_Init(void)
{
    USB_InitParam_T usbParam;

    RCM_ConfigUSBCLK(RCM_USB_DIV_1_5);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USB);
    
    HidMouse_GPIOInit();
    HidMouse_IntInit();
    
    usbParam.classReqHandler = NULL;
    usbParam.vendorReqHandler = NULL;
    usbParam.stdReqExceptionHandler = HidMouse_ReportDescriptor;
    
    usbParam.resetHandler = HidMouse_Reset;
    usbParam.epHandler = HidMouse_EPHandler;
    usbParam.deviceDesc = (USB_Descriptor_T *)&s_deviceDescriptor;
    usbParam.configurationDesc = (USB_Descriptor_T *)&s_configDescriptor;
    usbParam.stringDesc = (USB_Descriptor_T *)s_stringDescriptor;

    USB_Init(&usbParam);
}

