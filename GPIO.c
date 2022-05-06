
/*
 * GPIO.c
 *
 *  Created on: 29 abr 2022
 *      Author: angel
 */



#include "lib/include.h"
#include <CMSIS/Include/core_cm4.h>
#include <lib/TM4C123GH6PM.h>
#include <sys/_stdint.h>



extern void Configurar_GPIO_D(void)

{

   SYSCTL->RCGCGPIO |= (1<<3);// Activar el puerto,  DCBA->1000
   while((SYSCTL->PRGPIO&0x8) == 0){;} //ese 8 corresponde al valor en hexadecimal de 1000, para activar puerto D

   GPIOD->LOCK = 0x4C4F434B;//Desbloquea
   GPIOD->CR |= (1<<6)|(1<<7); // desbloquear pin 6


   //         D6 ENTRADA // D7 SALIDA
   GPIOD->DIR |=(0<<6) | (1<<7);
   GPIOD->PUR |=(1<<6);//para configurar pull up, pull down, en este caso Estado alto, solamente ocupa push button a tierra

   //Funciones alternativas
     GPIOD->AFSEL |=0x00;
     GPIOD->PCTL |= 0x00; //Tabla con GPIOCTL, vincula los pines al GPIO
     GPIOD->DEN |=(1<<6) | (1<<7); //Habilitarlos como digitales
     GPIOD -> AMSEL |=(0<<6)|(0<<7);

}

extern void habilitar_GPIO(void){

     //Habilitar interrupcionens
      GPIOD ->IM |= (0<<6);
      GPIOD->IS  |= (0<<6);
      GPIOD->IBE |= (0<<6);
      GPIOD->IEV |= (1<<6);
      GPIOD->RIS |= (0<<6);//??????????????
      GPIOD->IM  |= (1<<6);
      //n es igual a # de prioridad divido por 4, y truncado ese valor
      //ejemplo, n con la interrupción 51 es igual a 12
     //PUERTOD
             //n                //4n+3 4n+2 4n+1 4n




 NVIC->IP[0] = (NVIC->IP[0]&0x00FFFFFF) | (0x08000000);//0xFFFFFF00 corresponde a limpiar la posición del vector donde está el valor del número de interrupción,
                                                      //el 0x4 corresponde a agregar el valor en el vector que cayó (4n), y le otorgué la prioridad de 4, ni muy bajo ni muy alto
                //# de prioridad
 NVIC->ISER[0] = 0x8;//el número de prioridad en decimal, y el número de interrupción en hexadecimal





}

extern void GPIOD_ISR(void)
{

    if(GPIOD->RIS == (1<<6)){

            uint32_t i;
            uint8_t j;


            for (j=0; j<10;j++){

            GPIOD ->DATA |= 0x00000080;//Manda un pulso alto al LED
                for (i=0; i<100000;i++){}
                GPIOD ->DATA = 0x00000000;//Baja
                for (i=0; i<100000;i++){}

             }}

           GPIOD -> ICR |=(1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);// Limpiar todos los pines, no sólo los de entrada

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
