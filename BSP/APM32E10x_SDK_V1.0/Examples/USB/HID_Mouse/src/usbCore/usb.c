/*!
 * @file        usb.c
 *
 * @brief       USB driver     
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
#include "usb.h"
#include "apm32e10x_usb.h"
#include "usb_power.h"
#include "usb_standardRequest.h"

/** USB information */
static USB_Info_T s_usbInfo;

/*!
 * @brief       USB initialization
 *
 * @param       param: Initialization parameter
 *
 * @retval      None
 *
 * @note       
 */
void USB_Init(USB_InitParam_T *param)
{
    s_usbInfo.deviceDesc = param->deviceDesc;
    s_usbInfo.configurationDesc = param->configurationDesc;
    s_usbInfo.stringDesc = param->stringDesc;
    
    s_usbInfo.classReqHandler = param->classReqHandler;
    s_usbInfo.vendorReqHandler = param->vendorReqHandler;
    s_usbInfo.stdReqExceptionHandler = param->stdReqExceptionHandler;
    
    s_usbInfo.epHandler = param->epHandler;
    s_usbInfo.resetHandler = param->resetHandler;

#if USB_SELECT == USB1
    USBD2_Disable();
#else
    USB2_Enable();
#endif    
    USB_PowerOn();
}

/*!
 * @brief      USB Reset 
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void USB_Reset(void)
{
    s_usbInfo.configNum = USB_CONFIGURATION_NUM;
    s_usbInfo.curConfiguration = 0;
    s_usbInfo.curInterface = 0;
    s_usbInfo.curInterface = s_usbInfo.configurationDesc->pDesc[7];
    s_usbInfo.state = USB_STATE_WAIT_SETUP;
    s_usbInfo.numEP = USB_EP_NUM;
    s_usbInfo.packSizeEP = USB_EP_PACKET_SIZE;
    
    if(s_usbInfo.resetHandler)
    {
        s_usbInfo.resetHandler();
    }
}

/*!
 * @brief       USB low priority process       
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void USB_LowPriorityProc(void)
{
    USBD_EP_T ep;
    
    while(USBD_ReadIntFlag(USBD_INT_CTR))
    {
        ep = (USBD_EP_T)USBD_ReadEP();
        
        /** Endpoint 0 */
        if(ep == 0)
        {
            USBD_SetEPRxTxStatus(ep, USBD_EP_STATUS_NAK, USBD_EP_STATUS_NAK);
            
            /** Control in */
            if(USBD_ReadDir() == 0)
            {
                USBD_ResetEPTxFlag(ep);
                USB_CtrlInProcess();
            }
            else
            {
                USBD_ResetEPRxFlag(ep);
                
                /** Setup */
                if(USBD_ReadEPSetup(ep) == SET)
                {
                    USB_SetupProcess();
                }
                
                /** Control out */
                else
                {
                    USB_CtrlOutProcess();
                }
            }
        }
        else
        {
            if(s_usbInfo.epHandler)
            {
                if(USBD_ReadEPRxFlag(ep))
                {
                    USBD_ResetEPRxFlag(ep);
                    s_usbInfo.epHandler(ep, 0);
                }

                if(USBD_ReadEPTxFlag(ep))
                {
                    //DEBUG_INFO("EP: %d, dir: 1\r\n", ep);
                    USBD_ResetEPTxFlag(ep);
                    s_usbInfo.epHandler(ep, 1);
                }
            }
        }
    }
}

/*!
 * @brief       Setup process
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void USB_SetupProcess(void)
{
    uint8_t reqType;
    uint8_t dataBuf[8];
    USB_DevReqData_T *pReqData;
    
    pReqData = &s_usbInfo.reqData;
    
    USBD_ReadDataFromEP(USBD_EP_0, (uint8_t *)dataBuf, sizeof(dataBuf));

    pReqData->bmRequestType.byte = dataBuf[0];
    pReqData->bRequest = dataBuf[1];
    pReqData->wValue[0] = dataBuf[2];
    pReqData->wValue[1] = dataBuf[3];
    pReqData->wIndex[0] = dataBuf[4];
    pReqData->wIndex[1] = dataBuf[5];
    pReqData->wLength[0] = dataBuf[6];
    pReqData->wLength[1] = dataBuf[7];
    
    reqType = pReqData->bmRequestType.bit.type;
    
    if(reqType == USB_REQ_TYPE_STANDARD)
    {
        USB_StandardReqeust(&s_usbInfo);
    }
    else if(reqType == USB_REQ_TYPE_CLASS)
    {
        if(s_usbInfo.classReqHandler)
        {
            s_usbInfo.classReqHandler(pReqData);
        }
    }
    else if(reqType == USB_REQ_TYPE_VENDOR)
    {
        if(s_usbInfo.vendorReqHandler)
        {
            s_usbInfo.vendorReqHandler(pReqData);
        }

    }
    else
    {
        USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
    }
}

/*!
 * @brief       USB low priority process 
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void USB_HighPriorityProc(void)
{
    USBD_EP_T ep;
    
    while(USBD_ReadIntFlag(USBD_INT_CTR))
    {
        USBD_ClearIntFlag(USBD_INT_CTR);

        ep = USBD_ReadEP();
        
        if(USBD_ReadEPRxFlag(ep))
        {
            USBD_ResetEPRxFlag(ep);

            s_usbInfo.epHandler(ep, 0);
        }
        
        if(USBD_ReadEPTxFlag(ep))
        {
            USBD_ResetEPTxFlag(ep);

            s_usbInfo.epHandler(ep, 1);
        }
    }
}

/*!
 * @brief       USB Control in process
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void USB_CtrlInProcess(void)
{
    uint32_t tmp;

    if(s_usbInfo.state == USB_STATE_DATA_IN)
    {
        if(s_usbInfo.inBuf.packNum)
        {
            tmp = USB_MIN(s_usbInfo.inBuf.bufLen, s_usbInfo.packSizeEP);
        
            USBD_WriteDataToEP(USBD_EP_0, s_usbInfo.inBuf.buf, tmp);
            USBD_SetEPTxCnt(USBD_EP_0, tmp);     
            USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_VALID, USBD_EP_STATUS_VALID);
            
            s_usbInfo.inBuf.buf += tmp;
            s_usbInfo.inBuf.packNum--;
            s_usbInfo.inBuf.bufLen -= tmp;
        }
        else
        {
            s_usbInfo.state = USB_STATE_WAIT_STATUS_OUT;
            USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_VALID);
        }
    }
    else if(s_usbInfo.state == USB_STATE_WAIT_STATUS_IN)
    {
        if(s_usbInfo.reqData.bRequest == USB_SET_ADDRESS)
        {
            USBD_SetDeviceAddr(s_usbInfo.reqData.wValue[0]);
        }
        
        s_usbInfo.state = USB_STATE_STALLED;
        USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
    }
    else
    {
        USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);

        s_usbInfo.state = USB_STATE_STALLED;
    }

}


/*!
 * @brief       USB Control out process
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
void USB_CtrlOutProcess(void)
{
    uint32_t len;

    if(s_usbInfo.state == USB_STATE_DATA_OUT)
    {
        if(s_usbInfo.outBuf.packNum)
        {
            len = (s_usbInfo.outBuf.bufLen) >= s_usbInfo.packSizeEP ? s_usbInfo.packSizeEP : s_usbInfo.inBuf.bufLen;

            USBD_ReadDataFromEP(USBD_EP_0, s_usbInfo.outBuf.buf, len);

            s_usbInfo.inBuf.bufLen -= len;
            s_usbInfo.inBuf.buf += len;
            s_usbInfo.outBuf.packNum--;

            USBD_SetEPTxCnt(USBD_EP_0, 0);
            USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_VALID, USBD_EP_STATUS_VALID);
        }
        else
        {
            s_usbInfo.state = USB_STATE_WAIT_STATUS_IN;
            USBD_SetEPTxCnt(USBD_EP_0, 0);
            USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_VALID, USBD_EP_STATUS_VALID);
        }
    }
    else
    {
        USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_STALL, USBD_EP_STATUS_STALL);
        s_usbInfo.state = USB_STATE_STALLED;
    }
}


/*!
 * @brief       Send data or status in control in transation
 *
 * @param       buf:    Buffer pointer
 *
 * @param       len:    Buffer length
 *
 * @retval      None
 *
 * @note       
 */
void USB_CtrlInData(uint8_t *buf, uint32_t len)
{
    if(len)
    {
        if(len >= s_usbInfo.packSizeEP)
        {
            s_usbInfo.inBuf.bufLen = len - s_usbInfo.packSizeEP;
            s_usbInfo.inBuf.buf = buf + s_usbInfo.packSizeEP;
            s_usbInfo.inBuf.packNum = (s_usbInfo.inBuf.bufLen / s_usbInfo.packSizeEP) + 1;

            USBD_WriteDataToEP(USBD_EP_0, buf, s_usbInfo.packSizeEP);
            USBD_SetEPTxCnt(USBD_EP_0, s_usbInfo.packSizeEP);
            USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_VALID, USBD_EP_STATUS_VALID);  

            s_usbInfo.state = USB_STATE_DATA_IN;
        }
        else
        {
            USBD_WriteDataToEP(USBD_EP_0, buf, len);
            USBD_SetEPTxCnt(USBD_EP_0, len);
            USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_VALID, USBD_EP_STATUS_VALID); 
            
            s_usbInfo.state = s_usbInfo.reqData.bmRequestType.bit.dir ? USB_STATE_DATA_IN : USB_STATE_WAIT_STATUS_IN;
        }
    }
    else
    {
        USBD_SetEPTxCnt(USBD_EP_0, 0);
        USBD_SetEPRxTxStatus(USBD_EP_0, USBD_EP_STATUS_VALID, USBD_EP_STATUS_VALID); 
        
        s_usbInfo.state = s_usbInfo.reqData.bmRequestType.bit.dir ? USB_STATE_DATA_IN : USB_STATE_WAIT_STATUS_IN;
    } 
}

/*!
 * @brief       Read data or status in control out transation
 *
 * @param       buf:    Buffer pointer
 *
 * @param       len:    Buffer length
 *
 * @retval      None
 *
 * @note       
 */
void USB_CtrlOutData(uint8_t *buf, uint32_t len)
{
    s_usbInfo.outBuf.buf = buf;
    s_usbInfo.outBuf.bufLen = len;
    s_usbInfo.outBuf.packNum = (len / s_usbInfo.packSizeEP) + 1;
    
    USBD_SetEPRxStatus(USBD_EP_0, USBD_EP_STATUS_VALID);

    s_usbInfo.state = USB_STATE_DATA_OUT;
}
