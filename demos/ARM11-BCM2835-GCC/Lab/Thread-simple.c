/*
 * Thread-simple.c
 *
 *  Created on: Sep 17, 2015
 *      Author: Javier
 */


/*
 * threads.c
 *
 *  Created on: Sep 15, 2015
 *      Author: Javier
 */

// -------  Include Files --------
#include "ch.h"
#include "test.h"
#include "hal.h"
// -------------------------------


// Working Area creation
static WORKING_AREA(waThread1,128);


//---------------------


// Threads routine creation
static msg_t Thread1(void *p) {
  (void)p;
  chRegSetThreadName("blinker");
  while (TRUE) {
    palClearPad(ONBOARD_LED_PORT, ONBOARD_LED_PAD);
    chThdSleepMilliseconds(100);
    palSetPad(ONBOARD_LED_PORT, ONBOARD_LED_PAD);
    chThdSleepMilliseconds(900);
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

  /*
     * Set mode of onboard LED
     */

  palSetPadMode(ONBOARD_LED_PORT, ONBOARD_LED_PAD, PAL_MODE_OUTPUT);

  /*
     * Creates the blinker thread.
     */
  chThdCreateStatic(waThread1, sizeof(waThread1),NORMALPRIO, Thread1, NULL);


  /*
     * Events servicing loop.
     */
   while(TRUE)
   {
     return 0;
   }

}
