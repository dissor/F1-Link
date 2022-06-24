/*!
 * @file        usb_interrupt.c
 *
 * @brief       USB interrupt service routine  
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
#include "usb.h"
#include "apm32e10x_usb.h"
#include "usb_power.h"

/*!
 * @brief       USB interrupt service routine
 *
 * @param       None
 *
 * @retval      None
 *
 * @note       
 */
#if USB_SELECT == USB1 
void USBD1_LP_CAN1_RX0_IRQHandler(void)
#else
void USB2_LP_IRQHandler(void)
#endif
{
#if (USB_INT_SOURCE & USBD_INT_CTR)
    if(USBD_ReadIntFlag(USBD_INT_CTR))
    {
        USB_LowPriorityProc();
    }
#endif

#if (USB_INT_SOURCE & USBD_INT_RST) 
    if(USBD_ReadIntFlag(USBD_INT_RST))
    {
        USBD_ClearIntFlag(USBD_INT_RST);
        USB_Reset();
    }  
#endif

#if USB_INT_SOURCE & USBD_INT_PMAOU
    if(USB_ReadIntFlag(USB_INT_PMAOU))
    {
        USB_ClearIntFlag(USB_INT_PMAOU);
    }     
#endif

#if USB_INT_SOURCE & USBD_INT_ERR

    if(USB_ReadIntFlag(USB_INT_ERROR))
    {
        USB_ClearIntFlag(USB_INT_ERROR);
    }
#endif

#if USB_INT_SOURCE & USBD_INT_WKUP
    if(USBD_ReadIntFlag(USBD_INT_WKUP))
    {
        USB_Resume();
        USBD_ClearIntFlag(USBD_INT_WKUP);
    }
#endif

#if USB_INT_SOURCE & USBD_INT_SUS
    if(USBD_ReadIntFlag(USBD_INT_SUS))
    {
        USB_Suspend();
        USBD_ClearIntFlag(USBD_INT_SUS);
    }   
#endif

#if USB_INT_SOURCE & USBD_INT_SOF
    if(USB_ReadIntFlag(USB_INT_SOF))
    {
        USB_ClearIntFlag(USB_INT_SOF);
    }    
#endif

#if USB_INT_SOURCE & USBD_INT_ESOF
    if(USB_ReadIntFlag(USB_INT_ESOF))
    {
        USB_ClearIntFlag(USB_INT_ESOF);
    }    
#endif    
}

#if USB_SELECT == USB1 
void USBD1_HP_CAN1_TX_IRQHandler(void)
#else
void USB2_HP_IRQHandler(void)
#endif
{
    USB_HighPriorityProc();
}
