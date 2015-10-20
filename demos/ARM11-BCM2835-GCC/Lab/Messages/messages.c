/*
 * messages.c
 *
 *  Created on: Oct 19, 2015
 *      Author: opas3
 */
/*

ITESM
Lab Embeded
Lab 6 - ChibiOS - Part I
Activity 1

*/

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {
  Thread *tp;
  msg_t msg;
  (void)arg;
chprintf((BaseSequentialStream *)&SD1, "before do\r\n");
  do {
    tp = chMsgWait();
    msg = chMsgGet(tp);
    chprintf((BaseSequentialStream *)&SD1, "after do\r\n");
    /* process message here */

chprintf((BaseSequentialStream *)&SD1, "test\r\n");
    /* answering with the same message */
    chMsgRelease(tp, msg);
  } while (msg);

  return 0;
}

static WORKING_AREA(waThread2, 128);
static msg_t Thread2(void *p) {
chprintf((BaseSequentialStream *)&SD1, "sending\r\n");
  chMsgSend(*tp, 'A');
  return 0;
}


int main(void) {

    halInit();
    chSysInit();

    palSetPadMode(GPIO16_PORT, GPIO16_PAD, PAL_MODE_OUTPUT);
    sdStart(&SD1, NULL);
    chprintf((BaseSequentialStream *)&SD1, "Main (SD1 started)\r\n");
    chprintf((BaseSequentialStream *)&SD1, "---------------\r\n");
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

    //chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);


}



