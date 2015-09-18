/*
 * Lab6-Act1.c
 *
 *  Created on: Sep 18, 2015
 *      Author: Javier
 */

/*
 * Lab1-Act1.c
 *
 *  Created on: Sep 15, 2015
 *      Author: Javier
 */

/*   Modify the program (main.c) to display the messages “This is thread 1”,
 *   “This is thread 2”, etc. The messages should be displayed at the serial
 *   port. Ensure that the function chThdSleepMilliseconds() provided enough
 *   time so every thread has time to display message. Add the third thread
 *   and display the third message.
 */

//Time ----> 0
// *  T1 ........++++............++++............++++.....
// *  T2 ............++++............++++............++++.
// *  T3 ....++++........++++++++........++++++++........+

// -------  Include Files --------
#include "ch.h"
#include "test.h"
#include "hal.h"
// -------------------------------


// Working Area creation
static WORKING_AREA(waThread1,128);  // Normal Prio
static WORKING_AREA(waThread2,128);  // Normal Prio
static WORKING_AREA(waThread3,128);  // HIGH Prio
//---------------------


// Threads routine creation
static msg_t Thread1(void *p) {
  (void)p;
  chRegSetThreadName("Thread 1");
  while (TRUE) {

    chprintf((BaseSequentialStream *)&SD1, "This Is Thread 1\r\n");
    chThdSleepMilliseconds(2000);
  }
  return 0;
}

  static msg_t Thread2(void *p) {
  (void)p;
  chRegSetThreadName("Thread 2");
  while (TRUE) {
    chprintf((BaseSequentialStream *)&SD1, "This Is Thread 2\r\n");
    chThdSleepMilliseconds(2000);
  }
  return 0;
}

  static msg_t Thread3(void *p) {
  (void)p;
  chRegSetThreadName("Thread 3");
  while (TRUE) {
    chprintf((BaseSequentialStream *)&SD1, "This Is Thread 3\r\n");
    chThdSleepMilliseconds(1000);
  }
  return 0;
}

/*
 * Application entry point.
 */

int main (void)
{
  halInit();
  chSysInit();

    /*
    * Serial port initialization.
    */

   sdStart(&SD1, NULL);
   chprintf((BaseSequentialStream *)&SD1, "Main (SD1 started)\r\n");
   chprintf((BaseSequentialStream *)&SD1, "------------------\r\n");
   chprintf((BaseSequentialStream *)&SD1, "\r\n");
     /*
     * Set mode of onboard LED
     */

  palSetPadMode(ONBOARD_LED_PORT, ONBOARD_LED_PAD, PAL_MODE_OUTPUT);

    /*
     * Creates the blinker thread.
     */
  chThdCreateStatic(waThread1, sizeof(waThread1),NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2),NORMALPRIO, Thread2, NULL);
  chThdCreateStatic(waThread3, sizeof(waThread3),HIGHPRIO, Thread3, NULL);
    /*
     * Events servicing loop.
     */
   while(TRUE)
   {
     return 0;
   }

}
