/*
 * external.c

 *
 *  Created on: Oct 19, 2015
 *      Author: opas3
 */
#include "ch.h"
#include "hal.h"
#include "test.h"

// initialize semaphore as taken

SEMAPHORE_DECL(mysem, 1);

CH_IRQ_HANDLER(myIRQ) {

  CH_IRQ_PROLOGUE();

  /* Wakes up all the threads waiting on the semaphore.*/

  chSysLockFromIsr();
  chSemSignalI(&mysem);
  chSysUnlockFromIsr();
  CH_IRQ_EPILOGUE();

}

static WORKING_AREA(waThread2,128);
static msg_t Thread2(void *p){
 (void)p;
 chRegSetThreadName("blinker2");
 while (TRUE){
 chSemWait(&mysem);
 palTogglePad(GPIO17_PORT, GPIO17_PAD);
 chThdSleepMilliseconds(1000);
 }
return 0;
}

int main(void) {
  halInit();
  chSysInit();

  /*
   * Set mode of onboard LED
   */

  palSetPadMode(GPIO16_PORT,GPIO16_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO22_PORT,GPIO22_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO17_PORT,GPIO17_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO23_PORT,GPIO23_PAD, PAL_MODE_OUTPUT);
  /*
   * Creates the blinker thread.
   */
  //chThdCreateStatic(waThread1, sizeof(waThread1), HIGHPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
 // chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);
  /*
   * Events servicing loop.
   */
  return 0;
}

