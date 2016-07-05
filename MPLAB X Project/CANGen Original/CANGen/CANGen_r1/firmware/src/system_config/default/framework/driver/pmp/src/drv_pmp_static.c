/******************************************************************************/
/*                                                                            */
/*Company: ThaiGerTec Co., Ltd.                                               */
/*                                                                            */
/*Project: miniHILBaseSoftware                                                */
/*                                                                            */
/*File Name: drv_pmp_static.c                                                 */
/*                                                                            */
/*Summary: drv_pmp_static function implementations for communicate by Parallel*/
/*Master Port peripheral bus                                                  */
/*                                                                            */
/*Version: 1.0                                                                */
/*                                                                            */
/*Date created: 27 May 2015                                                   */
/*                                                                            */
/*Created by: Ruethaichonnanee Tantiwit                                       */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* MODIFICATION HISTORY:                                                      */
/*                                                                            */
/* Date:       Name:                       Change Description:                */
/*                                                                            */
/* 27.05.2015  Ruethaichonnanee Tantiwit   Create file                        */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/**
 * @defgroup A4 Parallel Master Port driver
 * @ingroup A1
 * @brief This file have a function about Parallel Master Port driver.
 * @{
 */

/****************************** include file **********************************/
#include "..\drv_pmp_static.h"

/**
 * @brief You will initial function before doing everything about this driver.
 * @param void
 * @return void
 */
void DRV_PMP0_Initialize(void)
{
    PLIB_PMP_Disable(PMP_ID_0);
    PLIB_PMP_Enable(PMP_ID_0);
}

/**
 * @brief You must set mode configuration after initial driver.
 * @param void
 * @return void
 */
void DRV_PMP0_ModeConfig(void)
{
    PLIB_PMP_Disable(PMP_ID_0);

    //Configure Main Communication Mode
    PLIB_PMP_OperationModeSelect(PMP_ID_0, PMP_MASTER_READ_WRITE_STROBES_INDEPENDENT);

    // Set the multiplexing to PMP_MUX_LINES_16_ADDRESS_16_DATA. Address and data lines are multiplexed.
    PLIB_PMP_MultiplexModeSelect( PMP_ID_0, PMP_MUX_LINES_16_ADDRESS_16_DATA );

    // Select the interrupt mode
    PLIB_PMP_InterruptModeSelect( PMP_ID_0, PMP_INTERRUPT_NONE );

    // disable the auto increment/decrement of address after each read/write
    PLIB_PMP_AddressIncrementModeSelect( PMP_ID_0, PMP_ADDRESS_AUTO_INCREMENT );

    // Enable stop in Idle mode.
    PLIB_PMP_ExistsStopInIdleControl( PMP_ID_0 );

    //Set the data width size
    PLIB_PMP_DataSizeSelect(PMP_ID_0, PMP_DATA_SIZE_16_BITS);

    //Setup Read Strobe Registers
    PLIB_PMP_ReadWriteStrobePortEnable(PMP_ID_0);
    PLIB_PMP_ReadWriteStrobePolaritySelect(PMP_ID_0, PMP_POLARITY_ACTIVE_LOW);

    //Setup Write Strobe Registers
    PLIB_PMP_WriteEnableStrobePortEnable(PMP_ID_0);
    PLIB_PMP_WriteEnableStrobePolaritySelect(PMP_ID_0, PMP_POLARITY_ACTIVE_LOW);

    // Configure the wait states
    PLIB_PMP_WaitStatesDataSetUpSelect(PMP_ID_0, PMP_DATA_WAIT_TWO);
    PLIB_PMP_WaitStatesStrobeSelect(PMP_ID_0, PMP_STROBE_WAIT_3);
    PLIB_PMP_WaitStatesDataHoldSelect(PMP_ID_0, PMP_DATA_HOLD_2);

    // Enable address latch pin
    PLIB_PMP_AddressLatchStrobeEnable( PMP_ID_0, PMP_ADDRESS_LATCH_HIGH | PMP_ADDRESS_LATCH_LOW);

    PLIB_PMP_Enable(PMP_ID_0);
}

/**
 * @brief This function use for write data by PMP bus.
 * @param addr Set address where you want to place data.
 * @param data You can send data to PMP bus by this parameter.
 * @return void
 */
void DRV_PMP0_Write(uint16_t addr,uint16_t data)
{
    // Set address
    PLIB_PMP_AddressSet(PMP_ID_0, addr );
    // Wait bus ready
    while(PLIB_PMP_PortIsBusy(PMP_ID_0) == true);
    // Send data
    PLIB_PMP_MasterSend(PMP_ID_0, data);
}

/**
 * @brief This function use for read data by PMP bus.
 * @param addr Set address where you want to read data.
 * @param data You can keep data from PMP bus by this parameter.
 * @return void
 */
void DRV_PMP0_Read(uint16_t addr,uint16_t *data)
{
    // Set address
    PLIB_PMP_AddressSet(PMP_ID_0, addr );
    // Dummy read
    // Read data from buffer to PMDIN & from Slave to buffer
    while(PLIB_PMP_PortIsBusy(PMP_ID_0) == true);
    PLIB_PMP_MasterReceive(PMP_ID_0);
    // Actual data shifted from buffer to PMDIN
    while(PLIB_PMP_PortIsBusy(PMP_ID_0) == true);
    *data = PLIB_PMP_MasterReceive(PMP_ID_0);    
}


/*******************************************************************************
 End of File
/** @}*/
