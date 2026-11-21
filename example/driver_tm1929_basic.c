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
 * @file      driver_tm1929_basic.c
 * @brief     driver tm1929 basic source file
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

#include "driver_tm1929_basic.h"

static tm1929_handle_t gs_handle;        /**< tm1929 handle */

/**
 * @brief     basic example init
 * @param[in] addr_pin iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t tm1929_basic_init(tm1929_address_t addr_pin)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_TM1929_LINK_INIT(&gs_handle, tm1929_handle_t);
    DRIVER_TM1929_LINK_IIC_INIT(&gs_handle, tm1929_interface_iic_init);
    DRIVER_TM1929_LINK_IIC_DEINIT(&gs_handle, tm1929_interface_iic_deinit);
    DRIVER_TM1929_LINK_IIC_WRITE(&gs_handle, tm1929_interface_iic_write);
    DRIVER_TM1929_LINK_DELAY_MS(&gs_handle, tm1929_interface_delay_ms);
    DRIVER_TM1929_LINK_DEBUG_PRINT(&gs_handle, tm1929_interface_debug_print);
    
    /* set the address */
    res = tm1929_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: set addr pin failed.\n");
       
        return 1;
    }
    
    /* init */
    res = tm1929_init(&gs_handle);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: init failed.\n");
       
        return 1;
    }
    
    /* disable shutdown */
    res = tm1929_set_shutdown(&gs_handle, TM1929_BOOL_FALSE);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: set shutdown failed.\n");
        (void)tm1929_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable led0 - led2 */
    res = tm1929_set_output_enable(&gs_handle, TM1929_OE_LED0_LED2, TM1929_BOOL_TRUE);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: set output enable failed.\n");
        (void)tm1929_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable led3 - led5 */
    res = tm1929_set_output_enable(&gs_handle, TM1929_OE_LED3_LED5, TM1929_BOOL_TRUE);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: set output enable failed.\n");
        (void)tm1929_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable led6 - led8 */
    res = tm1929_set_output_enable(&gs_handle, TM1929_OE_LED6_LED8, TM1929_BOOL_TRUE);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: set output enable failed.\n");
        (void)tm1929_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable led9 - led11 */
    res = tm1929_set_output_enable(&gs_handle, TM1929_OE_LED9_LED11, TM1929_BOOL_TRUE);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: set output enable failed.\n");
        (void)tm1929_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable led12 - led14 */
    res = tm1929_set_output_enable(&gs_handle, TM1929_OE_LED12_LED14, TM1929_BOOL_TRUE);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: set output enable failed.\n");
        (void)tm1929_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable led15 - led17 */
    res = tm1929_set_output_enable(&gs_handle, TM1929_OE_LED15_LED17, TM1929_BOOL_TRUE);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: set output enable failed.\n");
        (void)tm1929_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set all off */
    res = tm1929_set_all_off(&gs_handle);
    if (res != 0)
    {
        tm1929_interface_debug_print("tm1929: set all off failed.\n");
        (void)tm1929_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tm1929_basic_deinit(void)
{
    if (tm1929_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set brightness
 * @param[in] addr address
 * @param[in] *buffer pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 set brightness failed
 * @note      none
 */
uint8_t tm1929_basic_set_brightness(uint8_t addr, uint8_t *buffer, uint8_t len)
{
    /* set brightness */
    if (tm1929_set_brightness(&gs_handle, addr, buffer, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example set all off
 * @return status code
 *         - 0 success
 *         - 1 set all off failed
 * @note   none
 */
uint8_t tm1929_basic_set_all_off(void)
{
    if (tm1929_set_all_off(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example set all on
 * @return status code
 *         - 0 success
 *         - 1 set all on failed
 * @note   none
 */
uint8_t tm1929_basic_set_all_on(void)
{
    if (tm1929_set_all_on(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
