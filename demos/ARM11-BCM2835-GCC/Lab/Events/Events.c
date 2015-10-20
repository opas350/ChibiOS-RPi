/*
 * Events.c
 *
 *  Created on: Oct 19, 2015
 *      Author: opas3
 */


#include "ch.h"
#include "hal.h"
#include "chprintf.h"

static EVENTSOURCE_DECL(es1);

// Thread fetch message
static WORKING_AREA(waT1, 128);
static msg_t T1(void * arg) {
    //Mailbox* mbox = (Mailbox *)arg;
    //msg_t msg, result;
    //int x=41;
    //int y=0x41;

    (void) arg;

    while(TRUE) {
      //  result = chMBFetch(mbox, &msg, TIME_INFINITE);
        chEvtWaitAll( EVENT_MASK(0) );
        chprintf((BaseSequentialStream *)&SD1, "Waiting \r\n");
       /* if(result == RDY_OK) {
            if(msg == 1){
                palSetPad(GPIO16_PORT, GPIO16_PAD);
                chprintf((BaseSequentialStream *)&SD1, "Message 1 Fetched %c %c \r\n",x,y);
              }
            if(msg == 2){
                palClearPad(GPIO16_PORT, GPIO16_PAD);
              chprintf((BaseSequentialStream *)&SD1, "Message 2 Fetched\r\n");
            }
        } */
    }
return 0;
}

// Thread post message
static WORKING_AREA(waT2, 128);
static msg_t T2(void * arg) {
    (void) arg;
    while(TRUE) {
        chprintf((BaseSequentialStream *)&SD1, "Posting....\r\n");
        chThdSleepMilliseconds(2500);
        chEvtBroadcast(&es1);
return 0;
}
}
int main(void) {
    //Mailbox mbox;
    //msg_t mbox_buffer[1];
   // chMBInit(&mbox, mbox_buffer, 1);
    halInit();
    chSysInit();
    EventListener el1;



    chEvtInit(&es1);

    chEvtRegister(&es1, &el1, 0);



    palSetPadMode(GPIO16_PORT, GPIO16_PAD, PAL_MODE_OUTPUT);

    sdStart(&SD1, NULL);

    chprintf((BaseSequentialStream *)&SD1, "Main (SD1 started)\r\n");
    chprintf((BaseSequentialStream *)&SD1, "---------------\r\n");
    chThdCreateStatic(waT1, sizeof(waT1), NORMALPRIO, T1, NULL);
    chThdCreateStatic(waT2, sizeof(waT2), NORMALPRIO, T2, NULL);

    while (TRUE) {
        chThdSleepMilliseconds(500);
    }
}
