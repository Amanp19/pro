/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED0_GPIO_PORT_NUM       0
#define LED0_GPIO_BIT_NUM        22
#define LED1_GPIO_PORT_NUM       3
#define LED1_GPIO_BIT_NUM        26
#define LED2_GPIO_PORT_NUM       3
#define LED2_GPIO_BIT_NUM        25


/* Delay Function */
void delay()
    {
        for(long int i=0;i<=999;i++)
        {
            for(long int j=0;j<=9999;j++);
        }
    }
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */

static void prvSetupHardware(void)
{
   SystemCoreClockUpdate();
      Board_Init();

    /* Initial LED0 state is off */
    Board_LED_Set(0, false);

    /* Initial LED1 state is off */
    Board_LED_Set(1, false);

    /* Initial LED2 state is off */
    Board_LED_Set(2, false);
}
static void vLEDTask1(void *pvParameters) {

while(1)
   {
        Chip_GPIO_WriteDirBit(LPC_GPIO, 0, 22, 1);  // turns Red Led on
        delay();
        Chip_GPIO_WriteDirBit(LPC_GPIO, 0, 22, 0);    // turns Red Led off
        delay();
        Chip_GPIO_WriteDirBit(LPC_GPIO, 3, 26,1);    // turns Blue Led on
        delay();
        Chip_GPIO_WriteDirBit(LPC_GPIO, 3,26,0);    // turns Blue Led off
        delay();
        Chip_GPIO_WriteDirBit(LPC_GPIO,3, 25,1);    // turns Green Led on
        delay();
        Chip_GPIO_WriteDirBit(LPC_GPIO, 3,25, 0);    // turns Green Led off
        delay();

    }
}

/*****************************************************************************
/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief main routine for FreeRTOS blinky example
 * @return Nothing, function should not exit
 */
int main(void)
{
prvSetupHardware();

xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
(xTaskHandle *) NULL);

 /* Start the scheduler */
 vTaskStartScheduler();

/* Should never arrive here */
return 1;
}


