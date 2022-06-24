/*!
 * @file        usb_StandardRequest.c
 *
 * @brief       USB standard request process 
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
 
#include "usb_StandardRequest.h"

/*!
 * @brief       Standard request get configuration
 *
 * @param       usbInfo:    USB Information
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardGetConfiguration(USB_Info_T *usbInfo)
{
    if(usbInfo->reqData.bmRequestType.bit.recipient == USB_RECIPIENT_DEVICE)
    {
        USB_CtrlInData(&usbInfo->curConfiguration, 1);

        USB_UserStdGetConfiguration();
        
        return 1;
    }
    
    return 0;
}

/*!
 * @brief       Standard request get descriptor
 *
 * @param       usbInfo:    USB Information
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardGetDescriptor(USB_Info_T *usbInfo)
{
    uint8_t ret = 1;
    uint32_t len = 0;
    uint8_t wValue0 = usbInfo->reqData.wValue[0];
    uint8_t wValue1 = usbInfo->reqData.wValue[1];
    
    if(wValue1 == USB_DESC_DEVICE)
    {
        len = USB_MIN(usbInfo->reqData.wLength[0], usbInfo->deviceDesc->size);
        USB_CtrlInData((uint8_t *)usbInfo->deviceDesc->pDesc, len);
    }
    else if(wValue1 == USB_DESC_CONFIGURATION)
    {
        len = USB_MIN(usbInfo->reqData.wLength[0], usbInfo->configurationDesc->size);
        USB_CtrlInData((uint8_t *)usbInfo->configurationDesc->pDesc, len);
    }
    else if(wValue1 == USB_DESC_STRING)
    {
        len = USB_MIN(usbInfo->reqData.wLength[0], usbInfo->stringDesc[wValue0].size);
        USB_CtrlInData((uint8_t *)usbInfo->stringDesc[wValue0].pDesc, len);
    }
    else
    {
        ret = 0;;
    }

    return ret;
}

/*!
 * @brief       Standard request get interface
 *
 * @param       usbInfo:    USB Information
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardGetInterface(USB_Info_T *usbInfo)
{
    USB_DevReqData_T *reqData = &usbInfo->reqData;
    
    if((reqData->bmRequestType.bit.recipient) == USB_RECIPIENT_INTERFACE)
    {
        USB_CtrlInData(&usbInfo->curInterface, 1);

        USB_UserStdGetInterface();
        
        return 1;
    }
    
    return 0;

}

/*!
 * @brief       Standard request get status
 *
 * @param       usbInfo:    USB Information
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardGetStatus(USB_Info_T *usbInfo)
{
    uint8_t ret = 1;
    USB_DevReqData_T *reqData = &usbInfo->reqData;

    uint8_t status[2] = {0, 0};
    
    if((usbInfo->reqData.bmRequestType.bit.recipient) == USB_RECIPIENT_DEVICE)
    {
        if(usbInfo->curFeature & (1 << 5))
        {
            status[0] |= 0x02;
        }

        if(usbInfo->curFeature & (1 << 6))
        {
            status[0] |= 0x01;
        }

        USB_CtrlInData(status, 2);

        USB_UserStdGetStdStatus(); 
    }

    else if((usbInfo->reqData.bmRequestType.bit.recipient) == USB_RECIPIENT_INTERFACE)
    {
        USB_CtrlInData(status, 2);

        USB_UserStdGetStdStatus(); 
    } 

    else if((usbInfo->reqData.bmRequestType.bit.recipient) == USB_RECIPIENT_ENDPOINT)
    {

        if(reqData->wIndex[0] & 0x80)
        {
            if(USBD_ReadEPTxStatus(reqData->wIndex[0] & 0x0f) == USBD_EP_STATUS_STALL)
            {
                status[0] |= 0x01;
            }
        }
        else
        {
            if(USBD_ReadEPRxStatus(reqData->wIndex[0] & 0x0f) == USBD_EP_STATUS_STALL)
            {
                status[0] |= 0x01;
            }

        }
        USB_CtrlInData(status, 2);

        USB_UserStdGetStdStatus();
    }   
    else
    {
        ret = 0;
    }

    return ret;
}


/*!
 * @brief       Standard request set address
 *
 * @param       usbInfo:    USB Information
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardSetAddress(USB_Info_T *usbInfo)
{
    USB_DevReqData_T *reqData = &usbInfo->reqData;
    
    if((reqData->wValue[0] < 127) && (reqData->wValue[1] == 0) && 
        (reqData->bmRequestType.bit.recipient == USB_RECIPIENT_DEVICE))
    {
        USB_CtrlInData((void *)0, 0);
        
        USB_UserStdSetDeviceAddr();

        return 1;
    }

    return 0;
}

/*!
 * @brief       Standard request set configuration
 *
 * @param       usbInfo:    USB Information
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardSetConfiguration(USB_Info_T *usbInfo)
{
    USB_DevReqData_T *reqData = &usbInfo->reqData;
    
    if((reqData->wValue[0] <= usbInfo->configNum) && (reqData->bmRequestType.bit.recipient == USB_RECIPIENT_DEVICE))
    {
        usbInfo->curConfiguration = reqData->wValue[0];

        USB_CtrlInData((void *)0, 0);

        USB_UserStdSetConfiguraion();
        
        return 1;
    }

    return 0;
}

/*!
 * @brief       Standard request set descriptor
 *
 * @param       usbInfo:    USB Information
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardSetDescriptor(USB_Info_T *usbInfo)
{
    USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);

    return 1;
}

/*!
 * @brief       Standard request set feature
 *
 * @param       usbInfo:    USB Informafeaturetion
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardSetFeature(USB_Info_T *usbInfo)
{
    uint8_t ret = 1;
    uint8_t ep;
    
    if((usbInfo->reqData.wValue[0] == USB_FEATURE_REMOTE_WAKEUP) && 
        (usbInfo->reqData.bmRequestType.bit.recipient) == USB_DESC_DEVICE)
    {
        usbInfo->curFeature |= (1 << 5);

        USB_CtrlInData((void *)0, 0);

        USB_UserStdSetDeivceFeature();
    }
    if((usbInfo->reqData.wValue[0] == USB_FEATURE_ENDPOINT_HALT) && 
        (usbInfo->reqData.bmRequestType.bit.recipient) == USB_DESC_ENDPOINT)
    {
        ep = usbInfo->reqData.wIndex[0] & 0x7f;

        if((ep < usbInfo->numEP) && (!usbInfo->curConfiguration))
        {
            if(usbInfo->reqData.wIndex[0] & 0x80)
            {
                USBD_SetEPTxStatus((USBD_EP_T)ep, USBD_EP_STATUS_STALL);
            }
            else
            {
                USBD_SetEPRxStatus((USBD_EP_T)ep, USBD_EP_STATUS_STALL);
            }

            USB_CtrlInData((void *)0, 0);

            USB_UserStdSetEndPointFeature();
        }
    }     
    else
    {
        ret = 0;
    }

    return ret;
}

/*!
 * @brief       Standard request set interface
 *
 * @param       usbInfo:    USB Informafeaturetion
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardSetInterface(USB_Info_T *usbInfo)
{
    if((usbInfo->reqData.bmRequestType.bit.recipient) == USB_RECIPIENT_INTERFACE)
    {
        usbInfo->curInterface = usbInfo->reqData.wIndex[0];
        usbInfo->curAltternateSetting = usbInfo->reqData.wValue[0];

        USB_CtrlInData((void *)0, 0);

        USB_UserStdSetInterface();

        return 1;
    }

    return 0;
}

/*!
 * @brief       Standard request clear feature
 *
 * @param       usbInfo:    USB Informafeaturetion
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
uint8_t USB_StandardClearFeature(USB_Info_T *usbInfo)
{
    uint8_t ret = 1;
    uint8_t ep;
    
    if((usbInfo->reqData.wValue[0] == USB_FEATURE_REMOTE_WAKEUP) && 
        (usbInfo->reqData.bmRequestType.bit.recipient) == USB_RECIPIENT_DEVICE)
    {
        usbInfo->curFeature &= ~(1 << 5);

        USB_CtrlInData((void *)0, 0);

        USB_UserStdClearFeature();
    }
    if((usbInfo->reqData.wValue[0] == USB_FEATURE_ENDPOINT_HALT) && 
        (usbInfo->reqData.bmRequestType.bit.recipient) == USB_RECIPIENT_ENDPOINT)
    {
        ep = usbInfo->reqData.wIndex[0] & 0x7f;

        if((ep < usbInfo->numEP) && (!usbInfo->curConfiguration))
        {
            if(usbInfo->reqData.wIndex[0] & 0x80)
            {
                USBD_SetEPTxStatus((USBD_EP_T)ep, USBD_EP_STATUS_VALID);
            }
            else
            {
                USBD_SetEPRxStatus((USBD_EP_T)ep, USBD_EP_STATUS_VALID);
            }

            USB_CtrlInData((void *)0, 0);

            USB_UserStdClearFeature();
        }
    }     
    else
    {
        ret = 0;
    }

    return ret;
}

/*!
 * @brief       USB request standard request
 *
 * @param       usbInfo:    USB Information
 *
 * @retval      0: Failed; 1: Success
 *
 * @note       
 */
void USB_StandardReqeust(USB_Info_T *usbInfo)
{
    uint8_t result = 1;
    
    uint8_t bRequest = usbInfo->reqData.bRequest;
    
    switch(bRequest)
    {
        case USB_GET_CONFIGURATION:
            result = USB_StandardGetConfiguration(usbInfo);
        break;

        case USB_GET_DESCRIPTOR:
            result = USB_StandardGetDescriptor(usbInfo);
        break;

        case USB_GET_INTERFACE:
            result = USB_StandardGetInterface(usbInfo);
        break;

        case USB_GET_STATUS:
            result = USB_StandardGetStatus(usbInfo);
        break;

        case USB_SET_ADDRESS:
            result = USB_StandardSetAddress(usbInfo);
        break;

        case USB_SET_CONFIGURATION:
            result = USB_StandardSetConfiguration(usbInfo);
        break;

        case USB_SET_DESCRIPTOR:
            result = USB_StandardSetDescriptor(usbInfo);
        break;

        case USB_SET_FEATURE:
            result = USB_StandardSetFeature(usbInfo);
        break;

        case USB_SET_INTERFACE:
            result = USB_StandardSetInterface(usbInfo);
            
        break;

        case USB_CLEAR_FEATURE:
            result = USB_StandardClearFeature(usbInfo);
        break;
        
        default:
            USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL); 
            usbInfo->state = USB_STATE_STALLED;
            break;
    }

    if(!result)
    {
        if(usbInfo->stdReqExceptionHandler)
        {
            usbInfo->stdReqExceptionHandler(&usbInfo->reqData);
        }
    }
}

