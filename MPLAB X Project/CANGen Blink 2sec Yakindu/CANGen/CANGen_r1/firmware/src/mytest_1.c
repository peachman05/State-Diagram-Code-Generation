#include "./mytest_1.h"

bool DRV_CAN0_ChannelMessageReceiveRaw(CAN_CHANNEL channelNum, CAN_RX_MSG_BUFFER* buffer);

CAN_RX_MSG_BUFFER myBuff[255];
uint8_t i = 0;
uint8_t myMessage[8] = {0, 1, 2, 3, 4, 5, 6, 7};
uint8_t loop_count;

typedef struct {
    uint8_t sig0;
}msg0_t;

typedef struct {
    uint32_t sig0;
    uint8_t sig1;
}msg5_t;

typedef struct {
    uint32_t sig0;
    uint32_t sig1;
}msg8_t;

msg0_t msg0;
msg5_t msg5;
msg8_t msg8;

void mytest1_init(void)
{
        msg0.sig0 = 0;

        msg5.sig0 = 0;
        msg5.sig1 = 0;

        msg8.sig0 = 0;
        msg8.sig1 = 0;
}




void mytest1_Task(void)
{
    /*Receive Message*/
    // Raw Message receive
    uint8_t result;

    if(loop_count == 10)
    {
        loop_count = 0;


        msg0.sig0++;
        DRV_CAN0_ChannelMessageTransmit(CAN_CHANNEL1, 0x000, 0, (uint8_t *) &msg0 );

        msg5.sig0++;
        msg5.sig1++;
        DRV_CAN0_ChannelMessageTransmit(CAN_CHANNEL1, 0x005, 5, (uint8_t *) &msg5);

        msg8.sig0++;
        msg8.sig1++;
        DRV_CAN0_ChannelMessageTransmit(CAN_CHANNEL1, 0x008, 8, (uint8_t *) &msg8);

        while(DRV_CAN0_ChannelMessageReceiveRaw(CAN_CHANNEL0, &myBuff[i]))
        {

        }
    }
    else
    {
        loop_count++;
    }

}


bool DRV_CAN0_ChannelMessageReceiveRaw(CAN_CHANNEL channelNum, CAN_RX_MSG_BUFFER* buffer)
{
    CAN_RX_MSG_BUFFER *RxMessage;
    CAN_CHANNEL_EVENT channelEvent;

    channelEvent = PLIB_CAN_ChannelEventGet(CAN_ID_1, channelNum);
// if yes
// Get tail buffer address
// copy to buffer
    if(channelEvent & CAN_RX_CHANNEL_NOT_EMPTY != 0)
    {
        RxMessage = (CAN_RX_MSG_BUFFER *)PLIB_CAN_ReceivedMessageGet(CAN_ID_1, channelNum);
        buffer->messageWord[0] = RxMessage->messageWord[0];
        buffer->messageWord[1] = RxMessage->messageWord[1];
        buffer->messageWord[2] = RxMessage->messageWord[2];
        buffer->messageWord[3] = RxMessage->messageWord[3];
        /* Call the PLIB_CAN_ChannelUpdate function to let
        the CAN module know that the message processing
        is done. */
        PLIB_CAN_ChannelUpdate(CAN_ID_1, channelNum);
        return true;
    }
    else{
        return false;
    }
}