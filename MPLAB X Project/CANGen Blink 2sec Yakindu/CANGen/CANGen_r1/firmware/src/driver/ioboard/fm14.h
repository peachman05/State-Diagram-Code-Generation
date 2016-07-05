/* 
 * File:   25lc640.h
 * Author: HWUser12
 *
 * Created on January 20, 2016, 2:38 PM
 */

#ifndef FM14_H
#define	FM14_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

// *****************************************************************************

#define SPI2_CS_PORT_ID          PORT_CHANNEL_G
#define SPI3_CS_PORT_ID          PORT_CHANNEL_D
#define SPI2_CS_PORT_PIN         PORTS_BIT_POS_9
#define SPI3_CS_PORT_PIN         PORTS_BIT_POS_14   //J4:46

#define SPI2_CS_SELECT()     SYS_PORTS_PinClear(PORTS_ID_0,SPI2_CS_PORT_ID,SPI2_CS_PORT_PIN)
#define SPI2_CS_DESELECT()   SYS_PORTS_PinSet(PORTS_ID_0,SPI2_CS_PORT_ID,SPI2_CS_PORT_PIN)
#define SPI3_CS_SELECT()     SYS_PORTS_PinClear(PORTS_ID_0,SPI3_CS_PORT_ID,SPI3_CS_PORT_PIN)
#define SPI3_CS_DESELECT()   SYS_PORTS_PinSet(PORTS_ID_0,SPI3_CS_PORT_ID,SPI3_CS_PORT_PIN)

// *****************************************************************************

#define WRSR    0x01
#define WRITE   0x02
#define READ    0x03
#define WRDI    0x04
#define RDSR    0x05
#define WREN    0x06


#define WRSR_SIZE    0x02
#define WRITE_SIZE   0x03
#define READ_SIZE    0x03
#define WRDI_SIZE    0x01
#define RDSR_SIZE    0x02
#define WREN_SIZE    0x01

// *****************************************************************************

typedef struct
{
    uint8_t Ins;
    uint8_t Data;

}status_t;


typedef struct
{
    uint8_t Ins;
    uint8_t addrH;
    uint8_t addrL;
    uint8_t writebuffer[32];

}eeprom_t;

// *****************************************************************************

void T_WRSR (uint8_t * writebuffer, uint8_t * readbuffer);
void T_RDSR (uint8_t * writebuffer, uint8_t * readbuffer);
void T_WRITE (uint8_t * writebuffer, uint8_t * readbuffer, uint8_t datasize);
void T_READ (uint8_t * writebuffer, uint8_t * readbuffer, uint8_t datasize);
void T_WRDI (uint8_t * writebuffer, uint8_t * readbuffer);
void T_WREN (uint8_t * writebuffer, uint8_t * readbuffer);

void D_WRSR (uint8_t * writebuffer, uint8_t * readbuffer);
void D_RDSR (uint8_t * writebuffer, uint8_t * readbuffer);
void D_WRITE (uint8_t * writebuffer, uint8_t * readbuffer, uint8_t datasize);
void D_READ (uint8_t * writebuffer, uint8_t * readbuffer, uint8_t datasize);
void D_WRDI (uint8_t * writebuffer, uint8_t * readbuffer);
void D_WREN (uint8_t * writebuffer, uint8_t * readbuffer);

// *****************************************************************************
#endif	/* 25LC640_H */

