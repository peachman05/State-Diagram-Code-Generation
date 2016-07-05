

#include "fm14_app.h"


fm14_t TERMINATOR __attribute__((space(data),address(XCPDATA_BEGINADDRESS)));
fm14_t DUTIN __attribute__((space(data),address(XCPDATA_DUTINADDRESS)));

void FM14_tasks ()
{
    uint8_t temp;
    if(TERMINATOR.Ins) {

        switch(TERMINATOR.Ins)
        {
            case WREN:
                T_WREN(&TERMINATOR.Ins, &TERMINATOR.readbuffer[0]);
              break;
            case WRDI:
                T_WRDI(&TERMINATOR.Ins, &TERMINATOR.readbuffer[0]);
              break;
            case RDSR:
                T_RDSR(&TERMINATOR.Ins, &TERMINATOR.readbuffer[0]);
              break;
            case WRSR:
                T_WRSR(&TERMINATOR.Ins, &TERMINATOR.readbuffer[0]);
              break;
            case READ:
            {
                uint8_t temp;

                temp = TERMINATOR.writebuffer[0];
                TERMINATOR.writebuffer[0] = TERMINATOR.writebuffer[1];// addressH
                TERMINATOR.writebuffer[1] = temp;                     // addressL
                T_READ(&TERMINATOR.Ins, &TERMINATOR.readbuffer[0], TERMINATOR.nbyte);
              break;
            }
            case WRITE:
            {
                uint8_t temp;

                temp = TERMINATOR.writebuffer[0];
                TERMINATOR.writebuffer[0] = TERMINATOR.writebuffer[1];// addressH
                TERMINATOR.writebuffer[1] = temp;                     // addressL
                T_WRITE(&TERMINATOR.Ins, &TERMINATOR.readbuffer[0], TERMINATOR.nbyte);
              break;
            }
            default:
              break;
        }
        TERMINATOR.nbyte = 0;
        TERMINATOR.Ins = 0;

    }
    if(DUTIN.Ins) {

        switch(DUTIN.Ins)
        {
            case WREN:
                D_WREN(&DUTIN.Ins, &DUTIN.readbuffer[0]);
              break;
            case WRDI:
                D_WRDI(&DUTIN.Ins, &DUTIN.readbuffer[0]);
              break;
            case RDSR:
                D_RDSR(&DUTIN.Ins, &DUTIN.readbuffer[0]);
              break;
            case WRSR:
                D_WRSR(&DUTIN.Ins, &DUTIN.readbuffer[0]);
              break;
            case READ:
            {
                uint8_t temp;

                temp = DUTIN.writebuffer[0];
                DUTIN.writebuffer[0] = DUTIN.writebuffer[1];     // addressH
                DUTIN.writebuffer[1] = temp;                     // addressL
                D_READ(&DUTIN.Ins, &DUTIN.readbuffer[0], DUTIN.nbyte);
              break;
            }
            case WRITE:
            {
                uint8_t temp;

                temp = DUTIN.writebuffer[0];
                DUTIN.writebuffer[0] = DUTIN.writebuffer[1];     // addressH
                DUTIN.writebuffer[1] = temp;                     // addressL
                D_WRITE(&DUTIN.Ins, &DUTIN.readbuffer[0], DUTIN.nbyte);
              break;
            }
            default:
              break;
        }
        DUTIN.nbyte = 0;
        DUTIN.Ins = 0;
        
    }
}
