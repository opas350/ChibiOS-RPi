/*
 * gpios.c
 *
 *  Created on: Oct 19, 2015
 *      Author: opas3
 */

#include "ch.h"
#include "hal.h"
#include "test.h"

static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *p) {
  (void)p;
  chRegSetThreadName("blinker");
  while (TRUE) {
/* palClearPad(GPIO18_PORT, GPIO18_PAD);
   chThdSleepMilliseconds(900);
   palSetPad(GPIO18_PORT, GPIO18_PAD);
  chThdSleepMilliseconds(900);
*/

   palTogglePad(GPIO16_PORT, GPIO16_PAD);
   palTogglePad(GPIO4_PORT, GPIO4_PAD);
   //palTogglePad(ONBOARD_LED_PORT, ONBOARD_LED_PAD);
   chThdSleepMilliseconds(500);
  }
  return 0;
}
static WORKING_AREA(waThread2,128);
static msg_t Thread2(void *p){
 (void)p;
 chRegSetThreadName("blinker2");
 while (TRUE){
 palTogglePad(GPIO17_PORT, GPIO17_PAD);
 chThdSleepMilliseconds(1000);
 }
return 0;
}

static WORKING_AREA(waThread3,128);
static msg_t Thread3(void *p){
 (void)p;
 chRegSetThreadName("blinker3");
 while (TRUE){
 palTogglePad(GPIO18_PORT, GPIO18_PAD);
 chThdSleepMilliseconds(1500);
 }
return 0;
}

static WORKING_AREA(waThread4,128);
static msg_t Thread4(void *p){
 (void)p;
 chRegSetThreadName("blinker4");
 while (TRUE){
 palTogglePad(GPIO22_PORT, GPIO22_PAD);
 chThdSleepMilliseconds(1500);
 }
return 0;
}

static WORKING_AREA(waThread5,128);

static msg_t Thread5(void *p){
 (void)p;
 chRegSetThreadName("blinker5");
 while (TRUE){
 palTogglePad(GPIO23_PORT, GPIO23_PAD);
 chThdSleepMilliseconds(1500);
 }
return 0;
}

static WORKING_AREA(waThread6,128);
static msg_t Thread6(void *p){
 (void)p;
 chRegSetThreadName("blinker6");
 while (TRUE){



 palTogglePad(GPIO24_PORT, GPIO24_PAD);

 chThdSleepMilliseconds(1500);

 }



return 0;

}



static WORKING_AREA(waThread7,128);

static msg_t Thread7(void *p){
 (void)p;
 chRegSetThreadName("blinker7");
 while (TRUE){
 palTogglePad(GPIO25_PORT, GPIO25_PAD);

 chThdSleepMilliseconds(1500);
 }
return 0;
}
/*
 * Application entry point.

 */
int main(void) {

  halInit();
  chSysInit();

  /*
   * Set mode of onboard LED
   */

  palSetPadMode(GPIO4_PORT,GPIO4_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO16_PORT,GPIO16_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO17_PORT,GPIO17_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO18_PORT,GPIO18_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO22_PORT,GPIO22_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO23_PORT,GPIO23_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO24_PORT,GPIO24_PAD, PAL_MODE_OUTPUT);
  palSetPadMode(GPIO25_PORT,GPIO25_PAD, PAL_MODE_OUTPUT);

  /*
   * Creates the blinker thread.
   */

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);
  chThdCreateStatic(waThread4, sizeof(waThread4), NORMALPRIO, Thread4, NULL);
  chThdCreateStatic(waThread5, sizeof(waThread5), NORMALPRIO, Thread5, NULL);
  chThdCreateStatic(waThread6, sizeof(waThread6), NORMALPRIO, Thread6, NULL);
  chThdCreateStatic(waThread7, sizeof(waThread7), NORMALPRIO, Thread7, NULL);

  /*
   * Events servicing loop.
   */

  chThdWait(chThdSelf());
  return 0;
}









