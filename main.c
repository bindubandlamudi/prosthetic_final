/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC16F18875
        Driver Version    :  2.00
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
void main(void) {
    //Initialize the Device
    SYSTEM_Initialize();
    uint8_t command;
    uint16_t dutycycle = 0;

    //Interrupts need to be enabled for this SLAVE PIC to read incoming commands from the MASTER PIC

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();


    while (1) {
        // The Slave Reads commands sent from the Master via UART
        command = EUSART_Read();
        if (command == '1') // A '1' signifies a true positive muscle flex and we intend to turn the motor ON 
        {
            // LED D4 on Curiosity HPC is turned on for servo hold(clockwise)

            LED_RA6_SetHigh();

            //Loop though dutycycle values for continuous motor rotation clockwise

            for (dutycycle = 20; dutycycle <= 85; dutycycle++) {
                PWM6_LoadDutyValue(dutycycle);
                __delay_ms(20);
            }
        }
        else if (command == '0') // A '0' signifies a true positive muscle release and we intend to turn the motor OFF
        {

            // LED D4 on Curiosity HPC is turned off for servo release(counter clockwise)

            LED_RA6_SetLow();

            //Loop though dutycycle values for continuous motor rotation counter-clockwise

            for (dutycycle = 85; dutycycle >= 20; dutycycle--) {
                PWM6_LoadDutyValue(dutycycle);
                __delay_ms(20);
            }

        }
    }
}
/**
 End of File
 */