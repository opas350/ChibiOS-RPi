/*
 * main.c
 *
 *  Created on: Oct 19, 2015
 *      Author: opas3
 */

#include "ch.h"
#include "hal.h"
#include "test.h"

static SEMAPHORE_DECL(sem1, 0);
static SEMAPHORE_DECL(sem2, 0);
static MUTEX_DECL(m1);

static WORKING_AREA(waThread1, 64);

static msg_t Thread1(void *p) {

    (void)p;

   // palSetPadMode(GPIO4_PORT,GPIO4_PAD, PAL_MODE_OUTPUT);

  while (!chThdShouldTerminate()) {
    // Wait for signal from thread 2.
    chSemWait(&sem1);
    // Turn LED off.
    palTogglePad(GPIO16_PORT, GPIO16_PAD);
    chMtxLock(&m1);
    chSysLock();
    palTogglePad(GPIO4_PORT, GPIO4_PAD);
    chThdSleepMilliseconds(50);
    chSysUnlock();
    chMtxUnlock();

   // chSemSignal(&sem2);
    //chSemSignal(&sem2);
  }
  return 0;
}

static WORKING_AREA(waThread2, 64);
static msg_t Thread2(void *p) {
    (void)p;

  //palSetPadMode(GPIO17_PORT,GPIO17_PAD, PAL_MODE_OUTPUT);
  while (!chThdShouldTerminate()) {
    // Wait for signal from thread 2.
    chSemWait(&sem1);

    // Turn LED off.
    chMtxLock(&m1);
    chSysLock();
    palTogglePad(GPIO17_PORT, GPIO17_PAD);
    chThdSleepMilliseconds(50);
    chSysUnlock();
    chMtxUnlock();
  }

  return 0;

}

static WORKING_AREA(waThread3, 64);
static msg_t Thread3(void *p) {
  (void)p;
  while (!chThdShouldTerminate()) {
    // Wait for signal from thread 2.
    chSemWait(&sem1);
    // Turn LED off.
    chMtxLock(&m1);
    chSysLock();
    palTogglePad(GPIO18_PORT, GPIO18_PAD);
    chThdSleepMilliseconds(50);
    chSysUnlock();
    chMtxUnlock();
  }
  return 0;

}



static WORKING_AREA(waThread4, 64);

static msg_t Thread4(void *p) {
  (void)p;
  while (!chThdShouldTerminate()) {
    // Wait for signal from thread 2.
    chSemWait(&sem1);
    // Turn LED off.

    chMtxLock(&m1);
    chSysLock();
    palTogglePad(GPIO22_PORT, GPIO22_PAD);
    chThdSleepMilliseconds(50);
    chSysUnlock();
    //chMtxUnlock();
  }
  return 0;

}

static WORKING_AREA(waThread5, 64);

static msg_t Thread5(void *p) {
  (void)p;
  while (!chThdShouldTerminate()) {
    // Wait for signal from thread 2.
    chSemWait(&sem1);
    // Turn LED off.
    chMtxLock(&m1);
    chSysLock();

    palTogglePad(GPIO23_PORT, GPIO23_PAD);
    chThdSleepMilliseconds(50);
    chSysUnlock();
    chMtxUnlock();

  }
  return 0;
}

static WORKING_AREA(waThread6, 64);

static msg_t Thread6(void *p) {
  (void)p;
  while (!chThdShouldTerminate()) {
    // Wait for signal from thread 2.

    chSemWait(&sem1);
    // Turn LED off.
    chMtxLock(&m1);
    chSysLock();
    palTogglePad(GPIO24_PORT, GPIO24_PAD);
    chThdSleepMilliseconds(50);
    chSysUnlock();
    chMtxUnlock();

  }
  return 0;
}

static WORKING_AREA(waThread7, 64);

static msg_t Thread7(void *p) {

  (void)p;

  while (!chThdShouldTerminate()) {
    // Wait for signal from thread 2.

    chSemWait(&sem1);

    // Turn LED off.
   chMtxLock(&m1);
    chSysLock();
    palTogglePad(GPIO25_PORT, GPIO25_PAD);
    chThdSleepMilliseconds(50);
    chSysUnlock();
    chMtxUnlock();

  }

  return 0;

}



//------------------------------------------------------------------------------

// main thread runs at NORMALPRIO

int main(void) {

    halInit();
  chSysInit();

  chMtxInit(&m1);
  palSetPadMode(GPIO4_PORT,GPIO4_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO16_PORT,GPIO16_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO17_PORT,GPIO17_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO18_PORT,GPIO18_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO22_PORT,GPIO22_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO23_PORT,GPIO23_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO24_PORT,GPIO24_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO25_PORT,GPIO25_PAD, PAL_MODE_OUTPUT);

  // start blink thread

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);
  chThdCreateStatic(waThread4, sizeof(waThread4), NORMALPRIO, Thread4, NULL);
  chThdCreateStatic(waThread5, sizeof(waThread5), NORMALPRIO, Thread5, NULL);
  chThdCreateStatic(waThread6, sizeof(waThread6), NORMALPRIO, Thread6, NULL);
  chThdCreateStatic(waThread7, sizeof(waThread7), NORMALPRIO, Thread7, NULL);



while(TRUE){

  chSemSignal(&sem1);

}

return 0;

}

//------------------------------------------------------------------------------

/*

int main(void) {

  halInit();

  chSysInit();

  chBSemInit(&sem, TRUE);
  chBSemReset(&sem, TRUE);


  //palSetPadMode(GPIO16_PORT,GPIO16_PAD, PAL_MODE_OUTPUT);

  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2x  , &sem);

  chBSemWait(&sem);

//chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

//chBSemSignal(&sem);

 //chThdWait(chThdSelf());
  return 0;
}
*/



