/*
 * SimpleSemphore.c
 *
 *  Created on: Oct 19, 2015
 *      Author: opas3
 */
// Simple Semphore with only two LEDS



#include "ch.h"

#include "hal.h"

#include "test.h"



static SEMAPHORE_DECL(sem1, 0);





static WORKING_AREA(waThread1, 64);



static msg_t Thread1(void *p) {



    palSetPadMode(GPIO18_PORT,GPIO18_PAD, PAL_MODE_OUTPUT);



  while (!chThdShouldTerminate()) {

    // Wait for signal from thread 2.

    chSemWait(&sem1);



    // Turn LED off.

    palTogglePad(GPIO16_PORT, GPIO16_PAD);

    palTogglePad(GPIO18_PORT, GPIO18_PAD);

  }

  return 0;

}







static WORKING_AREA(waThread2, 64);



static msg_t Thread2(void *p) {



  //pinMode(LED_PIN, OUTPUT);

  palSetPadMode(GPIO16_PORT,GPIO16_PAD, PAL_MODE_OUTPUT);

  palSetPadMode(GPIO22_PORT,GPIO22_PAD, PAL_MODE_OUTPUT);



  while (1) {

    palTogglePad(GPIO16_PORT, GPIO16_PAD);

    palTogglePad(GPIO22_PORT, GPIO22_PAD);



    // Sleep for 200 milliseconds.

    chThdSleepMilliseconds(200);



    // Signal thread 1 to turn LED off.

   // chSemSignal(&sem1);



    // Sleep for 200 milliseconds.

    chThdSleepMilliseconds(200);

  }

  return 0;

}





//------------------------------------------------------------------------------

// main thread runs at NORMALPRIO

int main(void) {

    halInit();

    chSysInit();





  // start blink thread

  chThdCreateStatic(waThread1, sizeof(waThread1),NORMALPRIO + 2, Thread1, NULL);



  chThdCreateStatic(waThread2, sizeof(waThread2),NORMALPRIO + 1, Thread2, NULL);

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



