#include "mbed.h"

/*
   This basic example just shows how to read the ADC internal channels raw values.
   Please look in the corresponding device reference manual for a complete
   description of how to make a temperature sensor, VBat or Vref measurement.
*/

AnalogIn   Sens1(A0);
AnalogIn   Sens2(A1);
AnalogIn   Sens3(A2);
AnalogIn   Sens4(A3);
AnalogIn   Sens5(A4);
AnalogIn   Sens6(A5);

Serial pc(USBTX, USBRX); // tx, rx

int main()
{
    //printf("\nSTM32 ADC internal channels reading example\n");
    while(1) {
     
        //char c = pc.getc();
        //if (c =='s')
        //{
            //printf("First_Sensor\n");
            //while (1)
            //{
       
        printf("%f,",Sens1.read());
        printf("%f%,",Sens2.read());
        printf("%f%, ", Sens3.read());
        printf("%f%, ", Sens4.read());
        printf("%f%, ", Sens5.read());
        printf("%f%\n", Sens6.read());
        thread_sleep_for(1000);
       // wait(1);
    //}
        //}
     }
}
