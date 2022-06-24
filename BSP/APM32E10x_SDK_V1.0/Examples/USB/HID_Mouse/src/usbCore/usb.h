/*!
 * @file        usb.h
 *
 * @brief       USB driver header file       
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
#ifndef USB_H_
#define USB_H_
#include "apm32e10x_usb.h"
#include "usb_config.h"

/** Get minimum value */
#define USB_MIN(a, b)      (a >= b ? b : a)

/** Get maximum value */
#define USB_MAX(a, b)      (a >= b ? a : b)
 
/**
 * @brief   USB request type
 */
enum
{
    USB_REQ_TYPE_STANDARD   = 0,
    USB_REQ_TYPE_CLASS      = 1,
    USB_REQ_TYPE_VENDOR     = 2,
    USB_REQ_TYPE_RESERVED   = 3
};

/**
 * @brief   USB recipient
 */
enum
{
    USB_RECIPIENT_DEVICE    = 0,
    USB_RECIPIENT_INTERFACE = 1,
    USB_RECIPIENT_ENDPOINT  = 2,
    USB_RECIPIENT_OTHER     = 3,
};

/**
 * @brief   USB standard device requests
 */
enum
{
    USB_GET_STATUS          = 0,
    USB_CLEAR_FEATURE       = 1,
    USB_SET_FEATURE         = 3,
    USB_SET_ADDRESS         = 5,
    USB_GET_DESCRIPTOR      = 6,
    USB_SET_DESCRIPTOR      = 7,
    USB_GET_CONFIGURATION   = 8,
    USB_SET_CONFIGURATION   = 9,
    USB_GET_INTERFACE       = 10,
    USB_SET_INTERFACE       = 11,
    USB_SYNCH_FRAME         = 12,
};

/**
 * @brief   USB descriptor types
 */
enum
{
    USB_DESC_DEVICE             = 1,
    USB_DESC_CONFIGURATION      = 2,
    USB_DESC_STRING             = 3,
    USB_DESC_INTERFACE          = 4,
    USB_DESC_ENDPOINT           = 5,
    USB_DESC_DEVICE_QUALIFIER   = 6,
    USB_DESC_OTHER_SPEED        = 7,
    USB_INTERFACE_POWER         = 8,
};

/**
 * @brief   USB standard feature 
 */
enum
{
    USB_FEATURE_ENDPOINT_HALT   = 0,
    USB_FEATURE_REMOTE_WAKEUP   = 1,
    USB_FEATURE_TEST_MODE       = 2
};

/**
 * @brief   USB internal state machine    
 */
typedef enum
{
    USB_STATE_WAIT_SETUP,
    USB_STATE_DATA_IN,
    USB_STATE_DATA_OUT,
    USB_STATE_WAIT_STATUS_IN,
    USB_STATE_WAIT_STATUS_OUT,
    USB_STATE_STALLED,
}USB_STATE_T;

/**
 * @brief   USB request type
 */
typedef union
{   
    uint8_t byte;
    
    struct
    {
        uint8_t recipient       : 5;
        uint8_t type            : 2;
        uint8_t dir             : 1;
    }bit;
}USB_REQ_TYPE_T;

/**
 * @brief   USB device request data
 */
typedef struct
{
    USB_REQ_TYPE_T  bmRequestType;
    uint8_t         bRequest;
    uint8_t         wValue[2];
    uint8_t         wIndex[2];
    uint8_t         wLength[2];
}USB_DevReqData_T;

/**
 * @brief   Descriptor structure
 */
typedef struct
{
    const uint8_t *pDesc;
    uint8_t size;
}USB_Descriptor_T;

/** USB request handler */
typedef void (*USB_ReqHandler_T)(USB_DevReqData_T *);

/** Endpoint handler */
typedef void (*USB_EPHandler_T)(uint8_t ep, uint8_t dir);

/** Reset handler */
typedef void (*USB_ResetHandler_T)(void);

/**
 * @brief   USB init parameter
 */
typedef struct
{
    USB_Descriptor_T *deviceDesc;               //!< Device descriptor
    USB_Descriptor_T *configurationDesc;        //!< Configuration descriptor
    USB_Descriptor_T *stringDesc;               //!< String descriptor

    USB_ReqHandler_T stdReqExceptionHandler;    //!< Standard request exception handler
    USB_ReqHandler_T classReqHandler;           //!< Class request handler
    USB_ReqHandler_T vendorReqHandler;          //!< vendor request handler

    USB_EPHandler_T  epHandler;                 //!< Endpoint handler   
    USB_ResetHandler_T resetHandler;            //!< Reset handler  
}USB_InitParam_T;

/**
 * @brief   Control transfer buffer
 */
typedef struct
{
    uint8_t *buf;
    uint32_t bufLen;
    uint8_t  packNum;
}USB_CtrlBuf_T;

/**
 * @brief   USB infomation
 */
typedef struct
{
    USB_STATE_T state;
    
    uint8_t curFeature;
    uint8_t curInterface;
    uint8_t curConfiguration;
    uint8_t curAltternateSetting;
    USB_DevReqData_T reqData;

    uint8_t numEP;
    uint8_t packSizeEP;

    uint8_t configNum;
    
    USB_CtrlBuf_T inBuf;
    USB_CtrlBuf_T outBuf;
    
    USB_Descriptor_T *deviceDesc;
    USB_Descriptor_T *configurationDesc;
    USB_Descriptor_T *stringDesc;
    USB_Descriptor_T *hidReportDesc;

    USB_ReqHandler_T stdReqExceptionHandler;
    USB_ReqHandler_T classReqHandler;
    USB_ReqHandler_T vendorReqHandler;

    USB_EPHandler_T  epHandler;
    USB_ResetHandler_T resetHandler; 
}USB_Info_T;

void USB_Init(USB_InitParam_T *param);
void USB_Reset(void);
void USB_CtrlOutData(uint8_t *buf, uint32_t len);
void USB_CtrlInData(uint8_t *buf, uint32_t len);
void USB_SetupProcess(void);
void USB_CtrlInProcess(void);
void USB_CtrlOutProcess(void);
void USB_LowPriorityProc(void);
void USB_HighPriorityProc(void);

#endif
