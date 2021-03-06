/*****************************************************************************
 *
 * \file
 *
 * \brief FreeRTOS and lwIP example for AVR32 UC3.
 *
 * Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 *****************************************************************************/

/*! \mainpage
 * \section intro Introduction
 * This documents data structures, functions, variables, defines, enums, and
 * typedefs in the software for the lwIP basic two-in-one web server and TFTP server demo (without DHCP) example.
 *
 * The given example is an example using freeRTOS, the current lwIP stack and MACB driver.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC for AVR32 and IAR Systems compiler
 * for AVR32. Other compilers may or may not work.
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/uc3">Atmel AVR UC3</A>.\n
 */


#include "common.h"
#include "display.h"
#include "sensor.h"
#include "app.h"


int main( void )
{

        static pcl_freq_param_t pcl_freq_param =
        {
          .cpu_f        = configCPU_CLOCK_HZ,
          .pba_f        = configPBA_CLOCK_HZ,
          .osc0_f       = FOSC0,
          .osc0_startup = OSC0_STARTUP
        };

        // Configure system clock
        if (pcl_configure_clocks(&pcl_freq_param) != PASS)
          return 42;


	sensor_data = xQueueCreate(8, sizeof(ACCData));
	display_data = xQueueCreate(8, sizeof(ACCData));


	/* Setup the LED's for output. */
	vParTestInitialise();

	/* Start the flash tasks just to provide visual feedback that the demo is
	executing. */
	//vStartLEDFlashTasks( mainLED_TASK_PRIORITY );

	/* 2) Start the ethernet tasks launcher. */
	//vStartEthernetTaskLauncher( configMAX_PRIORITIES );

	xTaskCreate(
		mysensortask
		,(const signed portCHAR *) "mysensortask"
		,configMINIMAL_STACK_SIZE*5
		,NULL
		,2
		,NULL
	);

	xTaskCreate(
		myapptask
		,(const signed portCHAR *) "myapptask"
		,configMINIMAL_STACK_SIZE*5
		,NULL
		,2
		,NULL
	);

	xTaskCreate(
		mydisplaytask
		,(const signed portCHAR *) "mydisplaytask"
		,configMINIMAL_STACK_SIZE*5
		,NULL
		,2
		,NULL
	);
	/* 3) Start FreeRTOS. */
	vTaskStartScheduler();

	/* Will only reach here if there was insufficient memory to create the idle task. */

	return 0;
}
/*-----------------------------------------------------------*/
