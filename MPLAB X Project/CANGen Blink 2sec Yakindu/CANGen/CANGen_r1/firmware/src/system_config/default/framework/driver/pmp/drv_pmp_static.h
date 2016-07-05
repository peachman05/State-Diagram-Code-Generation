/******************************************************************************/
/*                                                                            */
/*Company: ThaiGerTec Co., Ltd.                                               */
/*                                                                            */
/*Project: miniHILBaseSoftware                                                */
/*                                                                            */
/*File Name: drv_pmp_static.h                                                 */
/*                                                                            */
/*Summary: drv_pmp_static header file implementations for drv_pmp_static.c    */
/*Version: 1                                                                  */
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

#ifndef _DRV_PMP_STATIC_H
#define _DRV_PMP_STATIC_H

#include "peripheral/pmp/plib_pmp.h"


void DRV_PMP0_Initialize(void);

void DRV_PMP0_ModeConfig(void);

void DRV_PMP0_Read(uint16_t addr,uint16_t * data);

void DRV_PMP0_Write(uint16_t addr,uint16_t data);


#endif // #ifndef _DRV_PMP_STATIC_H