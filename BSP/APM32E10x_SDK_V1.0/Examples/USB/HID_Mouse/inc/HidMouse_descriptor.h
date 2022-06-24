/*!
 * @file        HidMouse_descriptor.h
 *
 * @brief       HID_MOUSE descriptor          
 *
 * @version     V1.0.0
 *
 * @date        2021-07-26
 *
 */
#ifndef HID_MOUSE_DESCRIPTOR_H_
#define HID_MOUSE_DESCRIPTOR_H_

#include <stdint.h>

#define HID_MOUSE_DEVICE_DESCRIPTOR_SIZE        (18)
#define HID_MOUSE_CONFIG_DESCRIPTOR_SIZE        (34)
#define HID_MOUSE_LANGID_STRING_SIZE            (4)
#define HID_MOUSE_VENDOR_STRING_SIZE            (16)
#define HID_MOUSE_PRODUCT_STRING_SIZE           (32)
#define HID_MOUSE_REPORT_DESCRIPTOR_SIZE        (74)
#define HID_MOUSE_SERIAL_STRING_SIZE            (12)

extern const uint8_t g_hidMouseDeviceDescriptor[HID_MOUSE_DEVICE_DESCRIPTOR_SIZE];
extern const uint8_t g_hidMouseConfigDescriptor[HID_MOUSE_CONFIG_DESCRIPTOR_SIZE];
extern const uint8_t g_hidMouseReportDescriptor[HID_MOUSE_REPORT_DESCRIPTOR_SIZE];
extern const uint8_t g_hidMouseLandIDString[HID_MOUSE_LANGID_STRING_SIZE];
extern const uint8_t g_hidMouseVendorString[HID_MOUSE_VENDOR_STRING_SIZE];
extern const uint8_t g_hidMouseProductString[HID_MOUSE_PRODUCT_STRING_SIZE];
extern const uint8_t g_hidMouseSerialString[HID_MOUSE_SERIAL_STRING_SIZE];

#endif
