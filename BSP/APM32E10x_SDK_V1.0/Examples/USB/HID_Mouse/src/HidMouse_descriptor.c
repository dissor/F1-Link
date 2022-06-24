/*!
 * @file        HidMouse_descriptor.c
 *
 * @brief       HID_MOUSE descriptor     
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
#include "HidMouse_descriptor.h"
#include "usb.h"

/**
 * @brief   Device descriptor
 */
const uint8_t g_hidMouseDeviceDescriptor[HID_MOUSE_DEVICE_DESCRIPTOR_SIZE] = 
{
    /** bLength */
    0x12,
    
    /** bDescriptorType */
    USB_DESC_DEVICE,
    
    /** bcdUSB */
    0x00, 0x02,
    
    /** bDeviceClass */
    0x00, 
    /** bDeviceSubClass */
    0x00, 
    /** bDeviceProtocol */
    0x00,
    /** bMaxPacketSize = 64 */
    0x40, 
    /** idVendor =  314b*/
    0x4b, 0x31,
    /** idProduct = 0103 */
    0x03, 0x01,
    /** bcdDevice = 1.00 */
    0x00, 0x01,
    
    /** Index of string descriptor describing manufacturer */
    1,
    /** Index of string descriptor describing product */
    2,
    /** Index of string descriptor describing the device serial number */
    3,
    /** bNumConfigurations */
    1,
};

/**
 * @brief   Configuration descriptor
 */
const uint8_t g_hidMouseConfigDescriptor[HID_MOUSE_CONFIG_DESCRIPTOR_SIZE] = 
{
    /** bLength */
    0x09, 
    /** bDescriptorType */
    USB_DESC_CONFIGURATION,
    /** wTotalLength */
    HID_MOUSE_CONFIG_DESCRIPTOR_SIZE & 0XFF, HID_MOUSE_CONFIG_DESCRIPTOR_SIZE >> 8,
    
    /** bNumInterfaces */
    0X01,
    /** bConfigurationValue */
    0X01,
    /** iConfiguration */
    0X00,
    /** bmAttributes */
    0XE0,
    /** MaxPower */
    0X32,

    /** bLength */
    0X09,
    /** bDescriptorType */
    USB_DESC_INTERFACE,
    /** bInterfaceNumber */
    0X00, 
    /** bAlternateSetting */
    0X00, 
    /** bNumEndpoints */
    0X01, 
    /** bInterfaceClass */
    0X03, 
    /** bInterfaceSubClass */
    0X01, 
    /** nInterfaceProtocol */
    0X02,
    /** iInterface */
    0X00,

    /** bLength */
    0X09,
    /** bDescriptorType = HID */
    0x21,
    /** bcdHID */
    0X00, 0X01,
    /** bCountryCode */
    0X00, 
    /** bNumDescriptors */
    0X01,
    /** bDescriptorType */
    0X22,
    /** wItemLength */
    HID_MOUSE_REPORT_DESCRIPTOR_SIZE & 0XFF, HID_MOUSE_REPORT_DESCRIPTOR_SIZE >> 8,

    /** bLength */
    0X07,
    /** bDescriptorType */
    USB_DESC_ENDPOINT,
    /** bEndpointAddress */
    0X81,
    /** bmAttributes */
    0X03,
    /** wMaxPacketSize */
    0X04, 0X00,
    /** bInterval */
    0X20
};

/**
 * @brief   HID report descriptor
 */
const uint8_t g_hidMouseReportDescriptor[HID_MOUSE_REPORT_DESCRIPTOR_SIZE] =
{
    0x05,
    0x01,
    0x09,
    0x02,
    0xA1,
    0x01,
    0x09,
    0x01,

    0xA1,
    0x00,
    0x05,
    0x09,
    0x19,
    0x01,
    0x29,
    0x03,

    0x15,
    0x00,
    0x25,
    0x01,
    0x95,
    0x03,
    0x75,
    0x01,

    0x81,
    0x02,
    0x95,
    0x01,
    0x75,
    0x05,
    0x81,
    0x01,

    0x05,
    0x01,
    0x09,
    0x30,
    0x09,
    0x31,
    0x09,
    0x38,

    0x15,
    0x81,
    0x25,
    0x7F,
    0x75,
    0x08,
    0x95,
    0x03,

    0x81,
    0x06,
    0xC0,
    0x09,
    0x3c,
    0x05,
    0xff,
    0x09,

    0x01,
    0x15,
    0x00,
    0x25,
    0x01,
    0x75,
    0x01,
    0x95,

    0x02,
    0xb1,
    0x22,
    0x75,
    0x06,
    0x95,
    0x01,
    0xb1,

    0x01,
    0xc0
};

/**
 * @brief   language ID string
 */
const uint8_t g_hidMouseLandIDString[HID_MOUSE_LANGID_STRING_SIZE] = 
{
    /** Size */
    HID_MOUSE_LANGID_STRING_SIZE,
    /** bDescriptorType */
    USB_DESC_STRING,
    0X09,0X04
};

/**
 * @brief   Vendor string
 */
const uint8_t g_hidMouseVendorString[HID_MOUSE_VENDOR_STRING_SIZE] = 
{
    /** Size */
    HID_MOUSE_VENDOR_STRING_SIZE,
    /** bDescriptorType */
    USB_DESC_STRING,
    'A', 0, 'P', 0, 'E', 0, 'X', 0, 'M', 0, 'I', 0, 'C', 0
};

/**
 * @brief   Product string
 */
const uint8_t g_hidMouseProductString[HID_MOUSE_PRODUCT_STRING_SIZE] = 
{
    HID_MOUSE_PRODUCT_STRING_SIZE,
    USB_DESC_STRING,
    'A', 0, 'P', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'H', 0,
    'I', 0, 'D', 0, ' ', 0, 'M', 0, 'o', 0, 'u', 0, 's', 0,
    'e', 0
};

/**
 * @brief   Serial string
 */
const uint8_t g_hidMouseSerialString[HID_MOUSE_SERIAL_STRING_SIZE] = 
{
    HID_MOUSE_SERIAL_STRING_SIZE,
    USB_DESC_STRING,

    'A', 0, 'P', 0, 'M', 0, '3', 0, '2', 0    
}; 

