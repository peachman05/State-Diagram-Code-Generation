/*******************************************************************************
  I2C Driver Functions for Static Single Instance Driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_i2c_static.c
	
  Summary:
    I2C driver impementation for the static single instance driver.

  Description:
    The I2C device driver provides a simple interface to manage the I2C
    modules on Microchip microcontrollers. This file contains implemenation
    for the I2C driver.
    
  Remarks:
    Static interfaces incorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.
    
    Static single-open interfaces also eliminate the need for the open handle.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
#include "framework/driver/i2c/drv_i2c_static.h"

// *****************************************************************************
// *****************************************************************************
// Section: Instance 1 static driver functions
// *****************************************************************************
// *****************************************************************************
void DRV_I2C1_Initialize(void)
{
    /* Initialize I2C1 */
    PLIB_I2C_BaudRateSet(I2C_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 400000);
    PLIB_I2C_StopInIdleDisable(I2C_ID_2);

    /* High frequency is enabled (**NOTE** PLIB function revereted) */
    PLIB_I2C_HighFrequencyDisable(I2C_ID_2);

    /* Enable I2C1 */
    PLIB_I2C_Enable(I2C_ID_2);
}

void DRV_I2C1_DeInitialize(void)
{
    /* Disable I2C1 */
    PLIB_I2C_Disable(I2C_ID_2);
}

// *****************************************************************************
// Section: Instance 1 Byte Transfer Functions (Master/Slave)
// *****************************************************************************
bool DRV_I2C1_SetUpByteRead(void)
{
    /* Check for recieve overflow */
    if ( PLIB_I2C_ReceiverOverflowHasOccurred(I2C_ID_2))  
    {
        PLIB_I2C_ReceiverOverflowClear(I2C_ID_2); 
        return false;
    }
	
    /* Initiate clock to receive */
    PLIB_I2C_MasterReceiverClock1Byte(I2C_ID_2);
    return true;
}

bool DRV_I2C1_WaitForReadByteAvailable(void)
{
	/* Wait for Recieve Buffer Full */
    if(PLIB_I2C_ReceivedByteIsAvailable(I2C_ID_2))
       return true;
    else
       return false;
}

uint8_t DRV_I2C1_ByteRead(void)
{	
    /* Return recieved value */
    return (PLIB_I2C_ReceivedByteGet(I2C_ID_2));
}

bool DRV_I2C1_ByteWrite(const uint8_t byte)
{
    /* Check for recieve overflow */
    if ( PLIB_I2C_ReceiverOverflowHasOccurred(I2C_ID_2))  
    {
        PLIB_I2C_ReceivedByteGet(I2C_ID_2);
		PLIB_I2C_ReceiverOverflowClear(I2C_ID_2); 
        return false;
    }
    
    /* Check for transmit overflow */
    if (PLIB_I2C_TransmitterOverflowHasOccurred(I2C_ID_2))
    {
		PLIB_I2C_TransmitterOverflowClear(I2C_ID_2);
        return false;
    }
    
    /* Transmit byte */
    PLIB_I2C_TransmitterByteSend(I2C_ID_2, byte);
    
    return true;
}

bool DRV_I2C1_WaitForByteWriteToComplete(void)
{
    /* Check for transmit busy */
    while(PLIB_I2C_TransmitterIsBusy(I2C_ID_2));

    /* Check to see if transmit has completed */
    while(!PLIB_I2C_TransmitterByteHasCompleted(I2C_ID_2));
	
    return true;
}

bool DRV_I2C1_WriteByteAcknowledged(void)
{
    /* Check to see if transmit ACKed = true or NACKed = false */
    if (PLIB_I2C_TransmitterByteWasAcknowledged(I2C_ID_2))
       return true;
    else
       return false;
}

// *****************************************************************************
// Section: Instance 1 I2C Master Mode Functions
// *****************************************************************************
void DRV_I2C1_BaudRateSet(I2C_BAUD_RATE baudRate)
{
    /* Disable I2C1 */
    PLIB_I2C_Disable(I2C_ID_2);
    
    /* Change baud rate */
    PLIB_I2C_BaudRateSet(I2C_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), baudRate);

    /* High frequency is enabled (**NOTE** PLIB function revereted) */
    PLIB_I2C_HighFrequencyDisable(I2C_ID_2);
 
    /* Enable I2C1 */
    PLIB_I2C_Enable(I2C_ID_2);       
}

bool DRV_I2C1_MasterBusIdle(void)
{
    if (PLIB_I2C_BusIsIdle(I2C_ID_2))
       return true;
    else
       return false;
}

bool DRV_I2C1_MasterStart(void)
{
    /* Check for recieve overflow */
    if ( PLIB_I2C_ReceiverOverflowHasOccurred(I2C_ID_2))  
    {
        PLIB_I2C_ReceiverOverflowClear(I2C_ID_2); 
        return false;
    }
    
    /* Check for transmit overflow */
    if (PLIB_I2C_TransmitterOverflowHasOccurred(I2C_ID_2))
    {
        PLIB_I2C_TransmitterOverflowClear(I2C_ID_2);
        return false;
    }

    /* Check for bus collision errors */
    if (PLIB_I2C_ArbitrationLossHasOccurred(I2C_ID_2))
    {
        return false;
    }
    
    /* Issue start */
    PLIB_I2C_MasterStart(I2C_ID_2);
       
    return true;
}

bool DRV_I2C1_WaitForStartComplete(void)
{
    /* Wait for start/restart sequence to finish  (hardware clear) */
    while(!PLIB_I2C_StartWasDetected(I2C_ID_2));
	 
    return true;
}

bool DRV_I2C1_MasterRestart(void)
{
    /* Check for recieve overflow */
    if ( PLIB_I2C_ReceiverOverflowHasOccurred(I2C_ID_2))  
    {
        PLIB_I2C_ReceiverOverflowClear(I2C_ID_2); 
        return false;
    }
    
    /* Check for transmit overflow */
    if (PLIB_I2C_TransmitterOverflowHasOccurred(I2C_ID_2))
    {
        PLIB_I2C_TransmitterOverflowClear(I2C_ID_2);
        return false;
    }
    
    /* Issue restart */
    PLIB_I2C_MasterStartRepeat(I2C_ID_2); 
       
    return true;    
}

bool DRV_I2C1_MasterStop(void)
{
    /* Check for transmit overflow */
    if (PLIB_I2C_TransmitterOverflowHasOccurred(I2C_ID_2))
    {
        PLIB_I2C_TransmitterOverflowClear(I2C_ID_2);
        return false;
    }
    
    /* Issue stop */
    PLIB_I2C_MasterStop(I2C_ID_2);  

#if __PIC32MZ
    while (!PLIB_I2C_StopWasDetected(I2C_ID_2));
    PLIB_I2C_Disable(I2C_ID_2);
    PLIB_I2C_Enable(I2C_ID_2);
#endif	
    
    return true;
}

bool DRV_I2C1_WaitForStopComplete(void)
{
    while (!PLIB_I2C_StopWasDetected(I2C_ID_2));
		
    return true;
}

void DRV_I2C1_MasterACKSend(void)
{
    /* Check if receive is ready to ack */
    if ( PLIB_I2C_MasterReceiverReadyToAcknowledge(I2C_ID_2) )
    {
        PLIB_I2C_ReceivedByteAcknowledge (I2C_ID_2, true);
    }    

}

void DRV_I2C1_MasterNACKSend(void)
{
    /* Check if receive is ready to nack */
    if ( PLIB_I2C_MasterReceiverReadyToAcknowledge(I2C_ID_2) )
    {
       PLIB_I2C_ReceivedByteAcknowledge (I2C_ID_2, false);
    }    
}

bool DRV_I2C1_WaitForACKOrNACKComplete(void)
{
    /* Check for ACK/NACK to complete */
    while(PLIB_I2C_ReceiverByteAcknowledgeHasCompleted(I2C_ID_2));
	 
    return true;
}



/*******************************************************************************
 End of File
*/