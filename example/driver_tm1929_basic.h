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
 * @file      driver_tm1929_basic.h
 * @brief     driver tm1929 basic header file
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

#ifndef DRIVER_TM1929_BASIC_H
#define DRIVER_TM1929_BASIC_H

#include "driver_tm1929_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tm1929_example_driver tm1929 example driver function
 * @brief    tm1929 example driver modules
 * @ingroup  tm1929_driver
 * @{
 */

/**
 * @brief     basic example init
 * @param[in] addr_pin iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t tm1929_basic_init(tm1929_address_t addr_pin);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tm1929_basic_deinit(void);

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
uint8_t tm1929_basic_set_brightness(uint8_t addr, uint8_t *buffer, uint8_t len);

/**
 * @brief  basic example set all on
 * @return status code
 *         - 0 success
 *         - 1 set all on failed
 * @note   none
 */
uint8_t tm1929_basic_set_all_on(void);

/**
 * @brief  basic example set all off
 * @return status code
 *         - 0 success
 *         - 1 set all off failed
 * @note   none
 */
uint8_t tm1929_basic_set_all_off(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
