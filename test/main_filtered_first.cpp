#include "mbed.h"

/*
   This basic example just shows how to read the ADC internal channels raw values.
   Please look in the corresponding device reference manual for a complete
   description of how to make a temperature sensor, VBat or Vref measurement.
*/

Timer t;

//AnalogIn   Sens1(A0);
//AnalogIn   Sens2(A1);
//AnalogIn   Sens3(A2);
//AnalogIn   Sens4(A3);
//AnalogIn   Sens5(A4);
//AnalogIn   Sens6(A5);

AnalogIn Sens[7] = {A0, A1, A2, A3, A4, A5, ADC_VREF};
//AnalogIn adc_vref(ADC_VREF);

   
//unsigned short Sensors[6] = {Sens1.read_u16(),Sens2.read_u16(),Sens3.read_u16(),Sens4.read_u16(),Sens5.read_u16(),Sens6.read_u16()};
//AnalogIn Sens[6] = {Sens1,Sens2,Sens3,Sens4,Sens5,Sens6};

//float Vin = 3.3;
//float Res1 = 1.775;
float Vout[6] = {0.0f};
float Res_PBGS[6] = {0.0f};
float Res1[6] = {5.2f, 5.234f, 5.3f, 5.258f, 5.243f, 5.06f};
//float filter_val1,filter_val2,filter_val3,filter_val4,filter_val5,filter_val6 = 0;
float filter_val[7] = {0.0f};
uint16_t Max_res = 0xFFFF;
Serial pc(USBTX, USBRX); // tx, rx

const uint8_t iter = 20;
unsigned short buf[7][iter] = {0};
unsigned short max_buf[7], min_buf[7] = {0};
unsigned int sum_buf[7] = {0};
float pseumed[7] = {0.0f};
float vref=0.0f;
uint16_t vref12 = 0;

int main()
{
    t.start();
    //printf("\nSTM32 ADC internal channels reading example\n");
    while (1)
    {

        //char c = pc.getc();
        //if (c =='s')
        //{
        //printf("First_Sensor\n");
        //while (1)
        //{
        if (!(t.read_ms() % 1000))
        {
            //uint16_t vref12 = adc_vref.read_u16() >> 4;
            //float vref = (3.0f * (*VREFINT_CAL_ADDR) / vref12 );


            for (u_int8_t ch = 0; ch < 6; ch++)
            {
                Vout[ch] = ((filter_val[ch]*filter_val[6]*8.5715f)/ Max_res)/Max_res ;
                Res_PBGS[ch] = Res1[ch] * Vout[ch] / ((filter_val[6]*8.5715f/Max_res) - Vout[ch]);
            }

            printf("%f,", Res_PBGS[0]);
            printf("%f,", Res_PBGS[1]);
            printf("%f, ", Res_PBGS[2]);
            printf("%f, ", Res_PBGS[3]);
            printf("%f, ", Res_PBGS[4]);
            printf("%f, ", Res_PBGS[5]);
            

            printf("%f\n", ((filter_val[6]*8.5715f/Max_res)));
            for (u_int8_t i = 0; i < 20; i++)
            {

                for (u_int8_t p = 0; p < 7; p++)
                {
                    for (u_int8_t j = 0; j < iter; j++)
                    {
                        
                        buf[p][j] = Sens[p].read_u16();
                        if (max_buf[p] <= buf[p][j])
                            max_buf[p] = buf[p][j];
                        if (min_buf[p] >= buf[p][j])
                            min_buf[p] = buf[p][j];
                        sum_buf[p] += buf[p][j];
                        wait_us(100);
                        
                    }
                    pseumed[p] = (sum_buf[p] - min_buf[p] - max_buf[p]) / (iter - 2);
                    sum_buf[p] = 0;
                    min_buf[p] = 0;
                    max_buf[p] = 0;
                    
                }

                

                filter_val[0] += (pseumed[0] - filter_val[0]) * 0.05f;
                filter_val[1] += (pseumed[1] - filter_val[1]) * 0.05f;
                filter_val[2] += (pseumed[2] - filter_val[2]) * 0.05f;
                filter_val[3] += (pseumed[3] - filter_val[3]) * 0.05f;
                filter_val[4] += (pseumed[4] - filter_val[4]) * 0.05f;
                filter_val[5] += (pseumed[5] - filter_val[5]) * 0.05f;
                filter_val[6] += (pseumed[6] - filter_val[6]) * 0.05f;
               // uint16_t vref12 = filter_val[6] .read_u16() >> 4;
               // float vref = (3.0f * (*VREFINT_CAL_ADDR) / vref12 );
            }
        }
        //thread_sleep_for(1000);
        // wait(1);
        //}
        //}
    }
}

/*


for (u_int8_t i = 0; i < 20; i++)
        {

           for(u_int8_t j=0;j<iter;j++)
        {   
            
            buf[0][j]=Sens1.read_u16();
            if (max_buf[0]<=buf[0][j])
                max_buf[0]=buf[0][j];
             if (min_buf[0]>=buf[0][j])
                min_buf[0]=buf[0][j];
            sum_buf[0] +=buf[0][j];
            HAL_Delay(1);

        }

        pseumed[0] = (sum_buf[0] - min_buf[0] - max_buf[0])/(iter-2);
        sum_buf[0] = 0.0;
        min_buf[0] = 0.0;
        max_buf[0] = 0.0;


            filter_val1 += (pseumed[0] - filter_val1) * 0.05;
            filter_val2 += (float(Sens2.read_u16()) - filter_val2) * 0.05;
            filter_val3 += (float(Sens3.read_u16()) - filter_val3) * 0.05;
            filter_val4 += (float(Sens4.read_u16()) - filter_val4) * 0.05;
            filter_val5 += (float(Sens5.read_u16()) - filter_val5) * 0.05;
            filter_val6 += (float(Sens6.read_u16()) - filter_val6) * 0.05;
            
        }
        }
        //thread_sleep_for(1000);
       // wait(1);
    //}
        //}
     }
}


*/