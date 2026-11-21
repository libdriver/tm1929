/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-12-01
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/12/01  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_tm1929_write_test.h"
#include "driver_tm1929_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <math.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                        /**< uart buffer */
volatile uint16_t g_len;                   /**< uart buffer length */

/**
 * @brief     tm1929 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t tm1929(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"hex", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    uint8_t j;
    uint8_t buffer[18];
    uint8_t hex_code = 127;
    char type[33] = "unknown";
    tm1929_address_t addr = TM1929_ADDRESS_0;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr = TM1929_ADDRESS_0;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = TM1929_ADDRESS_1;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    addr = TM1929_ADDRESS_2;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    addr = TM1929_ADDRESS_3;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* hex */
            case 2 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                hex_code = hex_data & 0xFF;
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_write", type) == 0)
    {
        /* run write test */
        if (tm1929_write_test(addr) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = tm1929_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* make brightness */
        for (j = 0; j < 18; j++)
        {
            buffer[j] = hex_code;
        }
        res = tm1929_basic_set_brightness(0, buffer, 18);
        if (res != 0)
        {
            tm1929_interface_debug_print("tm1929: set brightness failed.\n");
            (void)tm1929_basic_deinit();
            
            return 1;
        }
        
        /* output */
        tm1929_interface_debug_print("tm1929: set brightness 0x%02X.\n", hex_code);
        
        /* delay 10000ms */
        tm1929_interface_delay_ms(10000);
        
        /* deinit */
        (void)tm1929_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        tm1929_interface_debug_print("Usage:\n");
        tm1929_interface_debug_print("  tm1929 (-i | --information)\n");
        tm1929_interface_debug_print("  tm1929 (-h | --help)\n");
        tm1929_interface_debug_print("  tm1929 (-p | --port)\n");
        tm1929_interface_debug_print("  tm1929 (-t write | --test=write) [--addr=<0 | 1 | 2 | 3>]\n");
        tm1929_interface_debug_print("  tm1929 (-e write | --example=write) [--addr=<0 | 1 | 2 | 3>] [--hex=<num>]\n");
        tm1929_interface_debug_print("\n");
        tm1929_interface_debug_print("Options:\n");
        tm1929_interface_debug_print("      --addr=<0 | 1 | 2 | 3>           Set the chip iic address.([default: 0])\n");
        tm1929_interface_debug_print("  -e <write>, --example=<write>        Run the driver example.\n");
        tm1929_interface_debug_print("  -h, --help                           Show the help.\n");
        tm1929_interface_debug_print("      --hex=<num>                      Set the brightness.([default: 0x7F])\n");
        tm1929_interface_debug_print("  -i, --information                    Show the chip information.\n");
        tm1929_interface_debug_print("  -p, --port                           Display the pin connections of the current board.\n");
        tm1929_interface_debug_print("  -t <write>, --test=<write>           Run the driver test.\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        tm1929_info_t info;
        
        /* print tm1929 info */
        tm1929_info(&info);
        tm1929_interface_debug_print("tm1929: chip is %s.\n", info.chip_name);
        tm1929_interface_debug_print("tm1929: manufacturer is %s.\n", info.manufacturer_name);
        tm1929_interface_debug_print("tm1929: interface is %s.\n", info.interface);
        tm1929_interface_debug_print("tm1929: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tm1929_interface_debug_print("tm1929: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tm1929_interface_debug_print("tm1929: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tm1929_interface_debug_print("tm1929: max current is %0.2fmA.\n", info.max_current_ma);
        tm1929_interface_debug_print("tm1929: max temperature is %0.1fC.\n", info.temperature_max);
        tm1929_interface_debug_print("tm1929: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        tm1929_interface_debug_print("tm1929: SCL connected to GPIOB PIN8.\n");
        tm1929_interface_debug_print("tm1929: SDA connected to GPIOB PIN9.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register tm1929 function */
    shell_init();
    shell_register("tm1929", tm1929);
    uart_print("tm1929: welcome to libdriver tm1929.\n");

    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("tm1929: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("tm1929: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("tm1929: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("tm1929: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("tm1929: param is invalid.\n");
            }
            else
            {
                uart_print("tm1929: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
