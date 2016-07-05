


#include "xcp_usb.h"


USB_CDC_DATA USB_CDCData;
uint8_t ReadBuffer[kXcpMaxCTO];
//uint8_t WriteBuffer[kXcpMaxCTO];
uint8_t WriteBuffer[1024];

uint8_t Counter;

/**
 * USB CDC Device Events - Application Event Handler
 * @param index
 * @param event
 * @param pData
 * @param userData
 * @return
 */
USB_DEVICE_CDC_EVENT_RESPONSE APP_USBDeviceCDCEventHandler(USB_DEVICE_CDC_INDEX index ,USB_DEVICE_CDC_EVENT event ,void * pData,uintptr_t userData) {

    USB_CDC_DATA * appDataObject;
    appDataObject = (USB_CDC_DATA *)userData;
    USB_CDC_CONTROL_LINE_STATE * controlLineStateData;

    switch (event)
    {
        case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:
        {
       /*This means the host wants to know the current line coding. This is a control transfer request. Use the USB_DEVICE_ControlSend() function to send the data to host*/
            USB_DEVICE_ControlSend(appDataObject->deviceHandle,&appDataObject->getLineCodingData, sizeof(USB_CDC_LINE_CODING));
            break;
        }
        case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:
        {
       /* This means the host wants to set the line coding.This is a control transfer request. Use the USB_DEVICE_ControlReceive() function to receive the data from the host*/
            USB_DEVICE_ControlReceive(appDataObject->deviceHandle,&appDataObject->setLineCodingData, sizeof(USB_CDC_LINE_CODING));
            break;
        }
        case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:
        {
       /* This means the host is setting the control line state.Read the control line state. We will accept this request for now*/
            controlLineStateData = (USB_CDC_CONTROL_LINE_STATE *)pData;
            appDataObject->controlLineStateData.dtr = controlLineStateData->dtr;
            appDataObject->controlLineStateData.carrier = controlLineStateData->carrier;
            USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
            break;
        }
        case USB_DEVICE_CDC_EVENT_SEND_BREAK:
        {
       /* This means that the host is requesting that a break of the specified duration be sent. Read the break duration */
            appDataObject->breakData = ((USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *)pData)->breakDuration;
            break;
        }
        case USB_DEVICE_CDC_EVENT_READ_COMPLETE:
        {
       /* This means that the host has sent some data*/
            appDataObject->isReadComplete = true;
            break;
        }
        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:
        {
       /* The data stage of the last control transfer is complete. For now we accept all the data */
            USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
            break;
        }
        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:
        {
       /* This means the GET LINE CODING function data is valid. We dont do much with this data in this demo.*/
            break;
        }
        case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:
        {
       /* This means that the data write got completed. We can schedule the next read.*/
            appDataObject->isWriteComplete = true;
            break;
        }
        default:
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}

/**
 * Application USB Device Layer Event Handler.
 * @param event
 * @param eventData
 * @param context
 */
void APP_USBDeviceEventHandler ( USB_DEVICE_EVENT event, void * eventData, uintptr_t context )
{
    USB_DEVICE_EVENT_DATA_CONFIGURED *configuredEventData;

    switch (event)
    {
        case USB_DEVICE_EVENT_SOF:
        {
       /* User can implement for Start Of Frame event showing*/
            USB_CDCData.sofEventHasOccurred = true;
            break;
        }
        case USB_DEVICE_EVENT_RESET:
        {
       /* User can implement for Reset event showing*/
            USB_CDCData.isConfigured = false;
            break;
        }
        case USB_DEVICE_EVENT_CONFIGURED:
        {
       /* Check the configuratio. We only support configuration 1 */
            configuredEventData = (USB_DEVICE_EVENT_DATA_CONFIGURED*)eventData;
            if ( configuredEventData->configurationValue == 1)
            {
       /* User can implement for Configured event showing*/

       /* Register the CDC Device application event handler here.Note how the appData object pointer is passed as the user data */
                USB_DEVICE_CDC_EventHandlerSet(USB_DEVICE_CDC_INDEX_0, APP_USBDeviceCDCEventHandler, (uintptr_t)&USB_CDCData);
       /* Mark that the device is now configured */
                USB_CDCData.isConfigured = true;
            }
            break;
        }
        case USB_DEVICE_EVENT_POWER_DETECTED:
        {
       /* VBUS was detected. We can attach the device */
            USB_DEVICE_Attach(USB_CDCData.deviceHandle);
            break;
        }
        case USB_DEVICE_EVENT_POWER_REMOVED:
        {
       /* VBUS is not available any more. Detach the device. */
            USB_DEVICE_Detach(USB_CDCData.deviceHandle);
            break;
        }
        case USB_DEVICE_EVENT_SUSPENDED:
        {
       /* User can implement for Suspended event showing*/
            break;
        }
        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;
    }
}


/**
 * XCP initialization function
 */
void Xcp_Initialize ( void )
{
    USB_CDCData.deviceHandle = USB_DEVICE_HANDLE_INVALID;
    USB_CDCData.isConfigured = false;
    USB_CDCData.getLineCodingData.dwDTERate = 9600;
    USB_CDCData.getLineCodingData.bParityType = 0;
    USB_CDCData.getLineCodingData.bDataBits = 8;
    USB_CDCData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    USB_CDCData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    USB_CDCData.isReadComplete = true;
    USB_CDCData.isWriteComplete = true;
    USB_CDCData.sofEventHasOccurred = false;
    USB_CDCData.state = XCPUSB_INIT;

}


/**
 * This function recieve command and data from PC and response
 */

uint8_t loop = 1;

void XcpReceiveCommand(void)
{

    switch(USB_CDCData.state)
    {
        case XCPUSB_INIT:
        {
       /* Open the device layer */
            USB_CDCData.deviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,DRV_IO_INTENT_WRITE|DRV_IO_INTENT_NONBLOCKING);
            if(USB_CDCData.deviceHandle != USB_DEVICE_HANDLE_INVALID)
            {
            /* Register a callback with device layer to get event notification (for end point 0) */
                USB_DEVICE_EventHandlerSet(USB_CDCData.deviceHandle,APP_USBDeviceEventHandler,0);
                USB_CDCData.state = USB_WAIT_FOR_CONFIGURATION;

            }
            break;
        }
        case USB_WAIT_FOR_CONFIGURATION:
        {
       /* Check if the device was configured */
            if(USB_CDCData.isConfigured) {
            /* If the device is configured then lets start reading */
                USB_CDCData.state = USB_RECEIVEDATA;
            }
            break;
        }
         case USB_RECEIVEDATA:
        {
            if(USB_CDCData.isWriteComplete == true) {
                USB_CDCData.isWriteComplete = false;
                USB_CDCData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
                WriteBuffer[0] += 1;
                WriteBuffer[15] = WriteBuffer[15] ^ 0x55;
                USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,&USB_CDCData.writeTransferHandle,&WriteBuffer[0], 1024,USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
            }
            USB_CDCData.state = XCP_RECEIVECOMMAND;

//            if(USB_CDCData.isWriteComplete == true) {
//
//                USB_CDCData.state = XCP_RECEIVECOMMAND;
//                if(USB_CDCData.isReadComplete == true){
//
//                    USB_CDCData.isReadComplete = false;
//                    USB_CDCData.readTransferHandle =  USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
//                    USB_DEVICE_CDC_Read(USB_DEVICE_CDC_INDEX_0,&USB_CDCData.readTransferHandle,&ReadBuffer[0],USB_DEVICE_EP0_BUFFER_SIZE);
//                    if(USB_CDCData.readTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID) {
//
//                        USB_CDCData.state = XCP_ERROR;
//                        break;
//                    }
//                }
//            }
            break;
        }
        case XCP_RECEIVECOMMAND:
        {
            if(loop == 0)
            {
                loop = 1;
                USB_CDCData.state = USB_RECEIVEDATA;
            }
            else
            {
                loop--;
            }

//            uint8_t len;
//            uint8_t cro[kXcpMaxCTO];
//            if(USB_CDCData.isReadComplete == true) {
//
//                len = ReadBuffer[0];
//                Counter = ReadBuffer[1];
//                if(len !=0 & len <= kXcpMaxCTO) {
//
//                    memcpy(&cro[0],&ReadBuffer[2],len);
//
//                    XcpCommand((uint8_t *) &cro);
//                }
//                USB_CDCData.state = USB_RECEIVEDATA;
//            }
            break;
        }
        case XCP_ERROR:
        {
            USB_DEVICE_Close(USB_CDCData.deviceHandle);
            USB_CDCData.state = XCPUSB_INIT;
            break;
        }
    }
}

// Transmit a XCP packet
void ApplXcpSend( vuint8 len, BYTEPTR msg )
{

  #ifdef XCP_PACKET_CHECKSUM
    vuint8 checksum;
  #endif

  if (len == 0||len > kXcpMaxCTO) {

      return; // should not happen
  }

  else {
      WriteBuffer[0] = len;
      WriteBuffer[1] = Counter;
      memcpy(&WriteBuffer[2],msg,len);

    USB_CDCData.isWriteComplete = false;
    USB_CDCData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,&USB_CDCData.writeTransferHandle,&WriteBuffer[0],WriteBuffer[0]+2 ,USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);

  }
}


// Convert a XCP address to a pointer
MTABYTEPTR ApplXcpGetPointer( vuint8 addr_ext, vuint32 addr ) {

  addr_ext = addr_ext;
  return (MTABYTEPTR)addr;
}


 vuint8 ApplXcpUserService( MEMORY_ROM BYTEPTR pCmd, BYTEPTR pRes)
 {
     uint8_t * address;
     uint8_t * cmd;
     uint8_t * res;
	 
     cmd = (uint8_t *) pCmd;
     res = (uint8_t *) pRes;

     if(XCP2P_CRO_IOB != IOB_ID) {

         return (vuint8) XCP_CMD_OUT_OF_RANGE;
     }

     ApplXcpGetAddress(XCP2P_CRO_TGTPID);

     if(XCP2P_CRO_RW == 1) {

	memcpy(address,XCP2P_CRO_PARAM,XCP2P_CRO_NUMPARAM);
     }
     else {

        memcpy(XCP2P_CRM_DATA,address,XCP2P_CRO_NUMPARAM);
     }
     return (vuint8)XCP_CMD_OK;

 }
