#include "mbed.h"

/*
   This basic example just shows how to read the ADC internal channels raw values.
   Please look in the corresponding device reference manual for a complete
   description of how to make a temperature sensor, VBat or Vref measurement.
*/

Timer t;

AnalogIn   Sens1(A0);
AnalogIn   Sens2(A1);
AnalogIn   Sens3(A2);
AnalogIn   Sens4(A3);
AnalogIn   Sens5(A4);
AnalogIn   Sens6(A5);

float Vin = 3.3;
//float Res1 = 1.775;
float Res1[6] = {5.743,5.469,5.469,5.469,5.469,5.469};
float filter_val1,filter_val2,filter_val3,filter_val4,filter_val5,filter_val6 = 0;
uint16_t Max_res = 0xFFFF;
Serial pc(USBTX, USBRX); // tx, rx

int main()
{       
    t.start();
    //printf("\nSTM32 ADC internal channels reading example\n");
    while(1) {
        
     
        //char c = pc.getc();
        //if (c =='s')
        //{
            //printf("First_Sensor\n");
            //while (1)
            //{
        if (!(t.read_ms()%1000))
        {
            
             

        float Vout1 = (filter_val1/Max_res)*Vin;
        float Res_PBGS_1 = Res1[0]*Vout1/(Vin-Vout1);

        float Vout2 = (filter_val2/Max_res)*Vin;
        float Res_PBGS_2 = Res1[1]*Vout2/(Vin-Vout2);

        float Vout3 = (filter_val3/Max_res)*Vin;
        float Res_PBGS_3 = Res1[2]*Vout3/(Vin-Vout3);

        float Vout4 = (filter_val4/Max_res)*Vin;
        float Res_PBGS_4 = Res1[3]*Vout4/(Vin-Vout4);

        float Vout5 = (filter_val5/Max_res)*Vin;
        float Res_PBGS_5 = Res1[4]*Vout5/(Vin-Vout5);

        float Vout6 = (filter_val6/Max_res)*Vin;
        float Res_PBGS_6 = Res1[5]*Vout6/(Vin-Vout6); 

        printf("%f,",Res_PBGS_1);
        printf("%f,",Res_PBGS_2);
        printf("%f, ", Res_PBGS_3);
        printf("%f, ", Res_PBGS_4);
        printf("%f, ", Res_PBGS_5);
        printf("%f\n", Res_PBGS_6);

        for (u_int8_t i = 0; i < 20; i++)
        {
            filter_val1 += (float(Sens1.read_u16()) - filter_val1) * 0.1;
            filter_val2 += (float(Sens2.read_u16()) - filter_val2) * 0.1;
            filter_val3 += (float(Sens3.read_u16()) - filter_val3) * 0.1;
            filter_val4 += (float(Sens4.read_u16()) - filter_val4) * 0.1;
            filter_val5 += (float(Sens5.read_u16()) - filter_val5) * 0.1;
            filter_val6 += (float(Sens6.read_u16()) - filter_val6) * 0.1;
        }
        }
        //thread_sleep_for(1000);
       // wait(1);
    //}
        //}
     }
}
