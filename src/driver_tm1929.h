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
 * @file      driver_tm1929.h
 * @brief     driver tm1929 header file
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

#ifndef DRIVER_TM1929_H
#define DRIVER_TM1929_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tm1929_driver tm1929 driver function
 * @brief    tm1929 driver modules
 * @{
 */

/**
 * @addtogroup tm1929_basic_driver
 * @{
 */

/**
 * @brief tm1929 address enumeration definition
 */
typedef enum
{
    TM1929_ADDRESS_0 = 0x4E,        /**< addr pin connected to the VDD */
    TM1929_ADDRESS_1 = 0x46,        /**< addr pin connected to the GND */
    TM1929_ADDRESS_2 = 0x4A,        /**< addr pin connected to the SCL */
    TM1929_ADDRESS_3 = 0x4C,        /**< addr pin connected to the SDA */
} tm1929_address_t;

/**
 * @brief tm1929 bool enumeration definition
 */
typedef enum
{
    TM1929_BOOL_FALSE = 0x00,        /**< false */
    TM1929_BOOL_TRUE  = 0x01,        /**< true */
} tm1929_bool_t;

/**
 * @brief tm1929 oe enumeration definition
 */
typedef enum
{
    TM1929_OE_LED0_LED2   = 0x00,        /**< led0 - led2 */
    TM1929_OE_LED3_LED5   = 0x01,        /**< led3 - led5 */
    TM1929_OE_LED6_LED8   = 0x02,        /**< led6 - led8 */
    TM1929_OE_LED9_LED11  = 0x03,        /**< led9 - led11 */
    TM1929_OE_LED12_LED14 = 0x04,        /**< led12 - led14 */
    TM1929_OE_LED15_LED17 = 0x05,        /**< led15 - led17 */
} tm1929_oe_t;

/**
 * @brief tm1929 handle structure definition
 */
typedef struct tm1929_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
    uint8_t iic_addr;                                                                   /**< iic address */
    uint8_t shadow;                                                                     /**< shadow */
} tm1929_handle_t;

/**
 * @brief tm1929 information structure definition
 */
typedef struct tm1929_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} tm1929_info_t;

/**
 * @}
 */

/**
 * @defgroup tm1929_link_driver tm1929 link driver function
 * @brief    tm1929 link driver modules
 * @ingroup  tm1929_driver
 * @{
 */

/**
 * @brief     initialize tm1929_handle_t structure
 * @param[in] HANDLE pointer to a tm1929 handle structure
 * @param[in] STRUCTURE tm1929_handle_t
 * @note      none
 */
#define DRIVER_TM1929_LINK_INIT(HANDLE, STRUCTURE)         memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to a tm1929 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_TM1929_LINK_IIC_INIT(HANDLE, FUC)          (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to a tm1929 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_TM1929_LINK_IIC_DEINIT(HANDLE, FUC)        (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE pointer to a tm1929 handle structure
 * @param[in] FUC pointer to an iic_write function address
 * @note      none
 */
#define DRIVER_TM1929_LINK_IIC_WRITE(HANDLE, FUC)         (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a tm1929 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_TM1929_LINK_DELAY_MS(HANDLE, FUC)          (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a tm1929 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_TM1929_LINK_DEBUG_PRINT(HANDLE, FUC)       (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup tm1929_basic_driver tm1929 basic driver function
 * @brief    tm1929 basic driver modules
 * @ingroup  tm1929_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a tm1929 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1929_info(tm1929_info_t *info);

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to a tm1929 handle structure
 * @param[in] addr_pin address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t tm1929_set_addr_pin(tm1929_handle_t *handle, tm1929_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to a tm1929 handle structure
 * @param[out] *addr_pin pointer to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1929_get_addr_pin(tm1929_handle_t *handle, tm1929_address_t *addr_pin);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a tm1929 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t tm1929_init(tm1929_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a tm1929 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t tm1929_deinit(tm1929_handle_t *handle);

/**
 * @brief     set shutdown
 * @param[in] *handle pointer to a tm1929 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set shutdown failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1929_set_shutdown(tm1929_handle_t *handle, tm1929_bool_t enable);

/**
 * @brief     set output enable
 * @param[in] *handle pointer to a tm1929 handle structure
 * @param[in] oe output enable
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set output enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1929_set_output_enable(tm1929_handle_t *handle, tm1929_oe_t oe, tm1929_bool_t enable);

/**
 * @brief     set brightness
 * @param[in] *handle pointer to a tm1929 handle structure
 * @param[in] addr address
 * @param[in] *buffer pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 set brightness failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 addr + len > 18
 *            - 5 buffer is over 127
 * @note      none
 */
uint8_t tm1929_set_brightness(tm1929_handle_t *handle, uint8_t addr, uint8_t *buffer, uint8_t len);

/**
 * @brief     set all off
 * @param[in] *handle pointer to a tm1929 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set all off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1929_set_all_off(tm1929_handle_t *handle);

/**
 * @brief     set all on
 * @param[in] *handle pointer to a tm1929 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set all on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1929_set_all_on(tm1929_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup tm1929_extern_driver tm1929 extern driver function
 * @brief    tm1929 extern driver modules
 * @ingroup  tm1929_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a tm1929 handle structure
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tm1929_set_reg(tm1929_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
