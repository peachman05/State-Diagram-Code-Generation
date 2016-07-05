#include "fm14.h"


/*-------------------------Terminator's EEPROM----------------------------------*/


void T_WRSR (uint8_t * writebuffer, uint8_t * readbuffer)
{
    status_t * tWRSR;

    tWRSR = (status_t *) writebuffer;
    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(&(tWRSR->Ins), readbuffer,WRSR_SIZE);
    SPI2_CS_DESELECT();
}


void T_RDSR (uint8_t * writebuffer, uint8_t * readbuffer)
{
    status_t * tRDSR;

    tRDSR = (status_t *) writebuffer;
    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(&(tRDSR->Ins), readbuffer, RDSR_SIZE);
    SPI2_CS_DESELECT();
}


void T_WRDI (uint8_t * writebuffer, uint8_t * readbuffer)
{

    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(writebuffer, readbuffer, WRDI_SIZE);
    SPI2_CS_DESELECT();
}


void T_WREN (uint8_t * writebuffer, uint8_t * readbuffer)
{

    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(writebuffer, readbuffer, WREN_SIZE);
    SPI2_CS_DESELECT();
}


void T_READ (uint8_t * writebuffer, uint8_t * readbuffer, uint8_t datasize)
{
    eeprom_t * tREAD;

    tREAD = (eeprom_t *) writebuffer;
    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(&(tREAD->Ins), readbuffer, (READ_SIZE + datasize));
    SPI2_CS_DESELECT();
}


void T_WRITE (uint8_t * writebuffer, uint8_t * readbuffer, uint8_t datasize)
{
    eeprom_t * tWRITE;

    tWRITE = (eeprom_t *) writebuffer;
    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(&(tWRITE->Ins), readbuffer, (WRITE_SIZE + datasize));
    SPI2_CS_DESELECT();
}

/*---------------------------DUT_IN's EEPROM------------------------------------*/


void D_WRSR (uint8_t * writebuffer, uint8_t * readbuffer)
{
    status_t * dWRSR;

    dWRSR = (status_t *) writebuffer;
    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(&(dWRSR->Ins), readbuffer, WRSR_SIZE);
    SPI2_CS_DESELECT();
}


void D_RDSR (uint8_t * writebuffer, uint8_t * readbuffer)
{
    status_t * dRDSR;

    dRDSR = (status_t *) writebuffer;
    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(&(dRDSR->Ins), readbuffer, RDSR_SIZE);
    SPI2_CS_DESELECT();
}


void D_WRDI (uint8_t * writebuffer, uint8_t * readbuffer)
{

    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(writebuffer, readbuffer, WRDI_SIZE);
    SPI2_CS_DESELECT();
}


void D_WREN (uint8_t * writebuffer, uint8_t * readbuffer)
{

    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(writebuffer, readbuffer, WREN_SIZE);
    SPI2_CS_DESELECT();
}


void D_READ (uint8_t * writebuffer, uint8_t * readbuffer, uint8_t datasize)
{
    eeprom_t * dREAD;

    dREAD = (eeprom_t *) writebuffer;
    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(&(dREAD->Ins), readbuffer, (READ_SIZE + datasize));
    SPI2_CS_DESELECT();
}


void D_WRITE (uint8_t * writebuffer, uint8_t * readbuffer, uint8_t datasize)
{
    eeprom_t * dWRITE;

    dWRITE = (eeprom_t *) writebuffer;
    SPI2_CS_SELECT();
    DRV_SPI0_BufferAddWriteRead(&(dWRITE->Ins), readbuffer, (WRITE_SIZE + datasize));
    SPI2_CS_DESELECT();
}


/*------------------------------------------------------------------------------*/