/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "main_functions.h"

#include "hx_drv_tflm.h"
#include "synopsys_wei_delay.h"
#include "stdio.h"

volatile void delay_ms(uint32_t ms_input);

char string_buf[100] = "test\n";

#define accel_scale 10

typedef struct
{
	uint8_t symbol;
	uint32_t int_part;
	uint32_t frac_part;
} accel_type;

// This is the default main used on systems that have the standard C entry
// point. Other devices (for example FreeRTOS or ESP32) that have different
// requirements for entry code (like an app_main function) should specialize
// this main.cc file in a target-specific subfolder.
int main(int argc, char* argv[]) 
{
    // flag
    volatile bool flag = false;
    // func 3.1.4
    int32_t int_buf;
	accel_type accel_x, accel_y, accel_z, accel_s;
	uint32_t msec_cnt = 0;
	uint32_t sec_cnt = 0;


    uint32_t msec_x100 = 100;
    

    hx_drv_uart_initial(UART_BR_115200);
    hx_drv_uart_print("T12\n");

    setup();

    // ==================================================
    //It will initial accelerometer with sampling rate 119 Hz, bandwidth 50 Hz, scale selection 4g at continuous mode.
	//Accelerometer operates in FIFO mode. 
	//FIFO size is 32
    
	if (hx_drv_accelerometer_initial() != HX_DRV_LIB_PASS)
		hx_drv_uart_print("Accelerometer Initialize Fail\n");
	else
		hx_drv_uart_print("Accelerometer Initialize Success\n");
    // ==================================================

    while (true) 
    {
        if (!flag) {
            // func 3.1.3
            hx_drv_led_off(HX_DRV_LED_RED);
            hx_drv_led_on(HX_DRV_LED_GREEN);
            delay_ms(100);
            hx_drv_led_off(HX_DRV_LED_GREEN);
            delay_ms(100);
            // func 3.1.4 =================================================
            uint32_t available_count = 0;
            float x, y, z;
            available_count = hx_drv_accelerometer_available_count();	
            for (int i = 0; i < available_count; i++) 
            {
                hx_drv_accelerometer_receive(&x, &y, &z);
            }
            int_buf = x * accel_scale; //scale value
            if(int_buf < 0)
            {
                int_buf = int_buf * -1;
                accel_x.symbol = '-';
            }
            else 
            {
                accel_x.symbol = '+';
            }
            accel_x.int_part = int_buf / accel_scale;
            accel_x.frac_part = int_buf % accel_scale;


            int_buf = y * accel_scale; //scale value
            if(int_buf < 0)
            {
                int_buf = int_buf * -1;
                accel_y.symbol = '-';
            }
            else 
            {
                accel_y.symbol = '+';
            }
            accel_y.int_part = int_buf / accel_scale;
            accel_y.frac_part = int_buf % accel_scale;


            int_buf = z * accel_scale; //scale value
            if(int_buf < 0)
            {
                int_buf = int_buf * -1;
                accel_z.symbol = '-';
            }
            else 
            {
                accel_z.symbol = '+';
            }
            accel_z.int_part = int_buf / accel_scale;
            accel_z.frac_part = int_buf % accel_scale;



            accel_s.int_part = (accel_x.int_part*accel_x.int_part) +(accel_y.int_part*accel_y.int_part)+(accel_z.int_part*accel_z.int_part);
            accel_s.frac_part = (accel_x.frac_part*accel_x.frac_part) +(accel_y.frac_part*accel_y.frac_part)+(accel_z.frac_part*accel_z.frac_part);

            sprintf(string_buf, "X:%c%1d.%1d | Y:%c%1d.%1d | Z:%c%1d.%1d | S:%2d.%1d G\n", 
                    accel_x.symbol, accel_x.int_part, accel_x.frac_part, 
                    accel_y.symbol, accel_y.int_part, accel_y.frac_part, 
                    accel_z.symbol, accel_z.int_part, accel_z.frac_part,
                    accel_s.int_part, accel_s.frac_part);
            hx_drv_uart_print(string_buf);
            if (accel_s.int_part > 3) {
                flag = true;
            }
        } else {
            int8_t a = 0;
            int8_t b = 0;
            a = msec_x100 / 10;
            b = msec_x100 % 10;
            //hx_drv_uart_print("Start time count: %5d.%1d\n", msec_x100 / 10, msec_x100 % 10);
            //hx_drv_uart_print("Detecting\n");
            loop(a, b);
            msec_x100 = msec_x100 - 5;
            if (msec_x100 == 0) {
                flag = false;
                msec_x100 = 100;
            }
            delay_ms(500);
        }
        
        // ============================================================
    }
}


volatile void delay_ms(uint32_t ms_input)
{
    volatile uint32_t i = 0;
    volatile uint32_t j = 0;

    for(i = 0; i < ms_input; i++)
        for(j = 0; j < 40000; j++);
}
