/* 
 * File:   xcp_usb.h
 * Author: HWUser12
 *
 * Created on December 9, 2015, 4:23 PM
 */

#ifndef XCP_USB_H
#define	XCP_USB_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"


#define END_XCP_ADDRESS                 0xA000FFFF
#define BEGIN_XCP_ADDRESS               0xA0005000


#define XCP2P_CRO_RW                    (*(cmd))
#define XCP2P_CRO_NUMPARAM              (*(cmd+1))
#define XCP2P_CRO_IOB                   (*(cmd+2))
#define XCP2P_CRO_TGTPID                (*(cmd+3))
#define XCP2P_CRO_PARAM                 (cmd+4)

#define XCP2P_CRM_DATA                   res

#define ApplXcpGetAddress(pid)          {address = (uint8_t *) (BEGIN_XCP_ADDRESS|pid);}

typedef enum
{
    XCPUSB_INIT=0,
    USB_WAIT_FOR_CONFIGURATION,
    USB_RECEIVEDATA,
    XCP_RECEIVECOMMAND,
    XCP_ERROR,

} USB_CDC_STATES;

typedef struct
{
    USB_CDC_STATES state;

    /* Device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE deviceHandle;

    /* Set Line Coding Data */
    USB_CDC_LINE_CODING setLineCodingData;

    /* Device configured state */
    bool isConfigured;

    /* Get Line Coding Data */
    USB_CDC_LINE_CODING getLineCodingData;

    /* Control Line State */
    USB_CDC_CONTROL_LINE_STATE controlLineStateData;

    /* Read transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE readTransferHandle;

    /* Write transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE writeTransferHandle;

    /* True if a character was read */
    bool isReadComplete;

    /* True if a character was written*/
    bool isWriteComplete;

    /* Flag determines SOF event occurrence */
    bool sofEventHasOccurred;

    /* Break data */
    uint16_t breakData;


} USB_CDC_DATA;



extern void Xcp_Initialize(void);
extern void XcpReceiveCommand(void);
uint8_t * Match_Address(uint8_t pid);


#endif	/* XCP_USB_H */

