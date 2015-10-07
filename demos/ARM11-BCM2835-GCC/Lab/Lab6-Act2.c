/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * Lab6-Act2.c
 *
 *  Created on: Sep 15, 2015
 *      Author: Javier
 */

/*
 * a)Port and modify the code listed below. Thread 1 sends a message to Thread 2.
 *  Thread 1 should send the letter A to Thread 2 and then wait for an acknowledgment.
 *  As soon as the acknowledgment is received, Thread 1 must increment the letter to
 *  send letter B and wait for the acknowledgment. Thread 1 should continuously send
 *  the message and send letter A again after sending letter Z.
 *  Display the messages using the serial port to indicate that the thread
 *  had properly send and received the messages.
 *
 *
 */

//Time ----> 0
// *  T1 ........++++............++++............++++.....
// *  T2 ............++++............++++............++++.
// *  T3 ....++++........++++++++........++++++++........+

// -------  Include Files --------
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

// -------------------
#define ALLOWED_DELAY MS2ST(5)
#define MB_SIZE 5
#define mbox_b 1

//static MAILBOX_DECL(mb1, mbox_b, MB_SIZE);

static WORKING_AREA(wacontrolthread, 128);
static msg_t controlthread(void *arg) {
  Mailbox* mb1 = (Mailbox *)arg;
  msg_t msg1;
   (void)arg;
   chRegSetThreadName("\r\n Control Thread \r\n");
   chprintf((BaseSequentialStream *)&SD1, "\r\n Entering Control Thread\r\n");
        msg1=0x41;
        chprintf((BaseSequentialStream *)&SD1, "\r\n message %c \r\n",msg1);
        chMBPost(mb1,0x41,TIME_INFINITE);
        chprintf((BaseSequentialStream *)&SD1, "\r\n MB Posted \r\n");
        chThdSleepMilliseconds(500);
        chThdWait(chThdSelf());
}

static WORKING_AREA(waThread1, 128);
static msg_t Thread1(void *arg) {
   (void)arg;
   Mailbox* mb1 = (Mailbox *)arg;
   msg_t msg1, status1;
   chRegSetThreadName("Thread 1");


   status1= chMBFetch(mb1,&msg1, TIME_INFINITE);

   chprintf((BaseSequentialStream *)&SD1, "\r\n Entering Thread 1\r\n");

   if(status1==RDY_OK){

     if (msg1==0x41)
       chprintf((BaseSequentialStream *)&SD1, "\r\n message: %c \r\n",msg1);
     else
       chprintf((BaseSequentialStream *)&SD1, "\r\n Error 1 \r\n");
       }

    if(status1==RDY_RESET){
      chprintf((BaseSequentialStream *)&SD1, "\r\n Error 2 \r\n");
       }

    if(status1==RDY_TIMEOUT){
         chprintf((BaseSequentialStream *)&SD1, "\r\n Error 3 \r\n");

   }

}
/*
 * Application entry point.
 */
int main(void) {
  halInit();
  chSysInit();
  static Mailbox mb1;
msg_t mbox_buff[1];
  chMBInit(&mb1,mbox_buff, MB_SIZE);

  /*
   * Serial port initialization.
   */
  sdStart(&SD1, NULL);
  chprintf((BaseSequentialStream *)&SD1, "Main (SD1 started)\r\n");
  chprintf((BaseSequentialStream *)&SD1, "\r\n ---------------\r\n");

  /*
   * Set mode of onboard LED
   */
  palSetPadMode(ONBOARD_LED_PORT, ONBOARD_LED_PAD, PAL_MODE_OUTPUT);

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(wacontrolthread, sizeof(wacontrolthread), NORMALPRIO, controlthread, &mb1);
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, &mb1);
  /*
   * Events servicing loop.
   */


  return 0;
}
