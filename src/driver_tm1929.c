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
 * @file      driver_tm1929.c
 * @brief     driver tm1929 source file
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

#include "driver_tm1929.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Titan Micro Electronics TM1929"        /**< chip name */
#define MANUFACTURER_NAME         "Titan Micro Electronics"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.4f                                    /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                                    /**< chip max supply voltage */
#define MAX_CURRENT               40.0f                                   /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                                  /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                                   /**< chip max operating temperature */
#define DRIVER_VERSION            1000                                    /**< driver version */

/**
 * @brief chip register definition
 */
#define TM1929_REG_RSTCTR               0x00        /**< reset register */
#define TM1929_REG_RGB_OE               0x01        /**< led enable register */
#define TM1929_REG_FIXBRIT_LED0         0x02        /**< led0 fix brightness register */
#define TM1929_REG_FIXBRIT_LED1         0x03        /**< led1 fix brightness register */
#define TM1929_REG_FIXBRIT_LED2         0x04        /**< led2 fix brightness register */
#define TM1929_REG_FIXBRIT_LED3         0x05        /**< led3 fix brightness register */
#define TM1929_REG_FIXBRIT_LED4         0x06        /**< led4 fix brightness register */
#define TM1929_REG_FIXBRIT_LED5         0x07        /**< led5 fix brightness register */
#define TM1929_REG_FIXBRIT_LED6         0x08        /**< led6 fix brightness register */
#define TM1929_REG_FIXBRIT_LED7         0x09        /**< led7 fix brightness register */
#define TM1929_REG_FIXBRIT_LED8         0x0A        /**< led8 fix brightness register */
#define TM1929_REG_FIXBRIT_LED9         0x0B        /**< led9 fix brightness register */
#define TM1929_REG_FIXBRIT_LED10        0x0C        /**< led10 fix brightness register */
#define TM1929_REG_FIXBRIT_LED11        0x0D        /**< led11 fix brightness register */
#define TM1929_REG_FIXBRIT_LED12        0x0E        /**< led12 fix brightness register */
#define TM1929_REG_FIXBRIT_LED13        0x0F        /**< led13 fix brightness register */
#define TM1929_REG_FIXBRIT_LED14        0x10        /**< led14 fix brightness register */
#define TM1929_REG_FIXBRIT_LED15        0x11        /**< led15 fix brightness register */
#define TM1929_REG_FIXBRIT_LED16        0x12        /**< led16 fix brightness register */
#define TM1929_REG_FIXBRIT_LED17        0x13        /**< led17 fix brightness register */

/**
 * @brief     write bytes
 * @param[in] *handle pointer to a tm1929 handle structure
 * @param[in] reg iic register address
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_tm1929_iic_write(tm1929_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_write(handle->iic_addr, reg, data, len) != 0)       /* write the register */
    {
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to a tm1929 handle structure
 * @param[in] addr_pin address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t tm1929_set_addr_pin(tm1929_handle_t *handle, tm1929_address_t addr_pin)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }
    
    handle->iic_addr = (uint8_t)addr_pin;        /* set pin */
    
    return 0;                                    /* success return 0 */
}

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to a tm1929 handle structure
 * @param[out] *addr_pin pointer to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1929_get_addr_pin(tm1929_handle_t *handle, tm1929_address_t *addr_pin)
{
    if (handle == NULL)                                       /* check handle */
    {
        return 2;                                             /* return error */
    }
    
    *addr_pin = (tm1929_address_t)(handle->iic_addr);        /* get pin */
    
    return 0;                                                 /* success return 0 */
}

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
uint8_t tm1929_init(tm1929_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->iic_init == NULL)                                    /* check iic_init */
    {
        handle->debug_print("tm1929: iic_init is null.\n");          /* iic_init is null */
       
        return 3;                                                    /* return error */
    }
    if (handle->iic_deinit == NULL)                                  /* check iic_deinit */
    {
        handle->debug_print("tm1929: iic_deinit is null.\n");        /* iic_deinit is null */
       
        return 3;                                                    /* return error */
    }
    if (handle->iic_write == NULL)                                   /* check iic_write */
    {
        handle->debug_print("tm1929: iic_write is null.\n");         /* iic_write is null */
       
        return 3;                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                    /* check delay_ms */
    {
        handle->debug_print("tm1929: delay_ms is null.\n");          /* delay_ms is null */
       
        return 3;                                                    /* return error */
    }
    
    if (handle->iic_init() != 0)                                     /* iic init */
    {
        handle->debug_print("tm1929: iic init failed.\n");           /* iic init failed */
       
        return 1;                                                    /* return error */
    }
    
    handle->shadow = 0x3F;                                           /* set all on */
    handle->inited = 1;                                              /* flag finish initialization */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t tm1929_deinit(tm1929_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    prev = 1;                                                                        /* set the bool */
    res = a_tm1929_iic_write(handle, TM1929_REG_RSTCTR, (uint8_t *)&prev, 1);        /* write reset register */
    if (res != 0)                                                                    /* check the result */
    {
        handle->debug_print("tm1929: write reset register failed.\n");               /* write reset register failed */
       
        return 4;                                                                    /* return error */
    }
    
    res = handle->iic_deinit();                                                      /* iic deinit */
    if (res != 0)                                                                    /* check result */
    {
        handle->debug_print("tm1929: iic deinit failed.\n");                         /* iic deinit failed */
       
        return 1;                                                                    /* return error */
    }
    handle->inited = 0;                                                              /* flag closed */
    
    return 0;                                                                        /* success return 0 */
}

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
uint8_t tm1929_set_shutdown(tm1929_handle_t *handle, tm1929_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    prev = enable;                                                                   /* set the bool */
    res = a_tm1929_iic_write(handle, TM1929_REG_RSTCTR, (uint8_t *)&prev, 1);        /* write reset register */
    if (res != 0)                                                                    /* check the result */
    {
        handle->debug_print("tm1929: write reset register failed.\n");               /* write reset register failed */
       
        return 1;                                                                    /* return error */
    }
    
    return 0;                                                                        /* success return 0 */
}

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
uint8_t tm1929_set_output_enable(tm1929_handle_t *handle, tm1929_oe_t oe, tm1929_bool_t enable)
{
    uint8_t res;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    handle->shadow &= ~(1 << (uint8_t)oe);                                                     /* clear settings */
    handle->shadow |= (uint8_t)enable << (uint8_t)oe;                                          /* set the bool */
    res = a_tm1929_iic_write(handle, TM1929_REG_RGB_OE, (uint8_t *)&handle->shadow, 1);        /* write led enable register */
    if (res != 0)                                                                              /* check the result */
    {
        handle->debug_print("tm1929: write led enable register failed.\n");                    /* write led enable register failed */
       
        return 1;                                                                              /* return error */
    }
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t tm1929_set_brightness(tm1929_handle_t *handle, uint8_t addr, uint8_t *buffer, uint8_t len)
{
    uint8_t res;
    uint8_t i;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    if (addr + len > 18)                                                                  /* check range */
    {
        handle->debug_print("tm1929: addr + len > 18.\n");                                /* addr + len > 18 */
       
        return 4;                                                                         /* return error */
    }
    for (i = 0; i < len; i++)                                                             /* check all */
    {
        if (buffer[i] > 127)                                                              /* check range */
        {
            handle->debug_print("tm1929: buffer %d is over 127.\n");                      /* buffer is over 127 */
           
            return 5;                                                                     /* return error */
        }
    }
    
    res = a_tm1929_iic_write(handle, TM1929_REG_FIXBRIT_LED0 + addr, buffer, len);        /* write fix brightness register */
    if (res != 0)                                                                         /* check the result */
    {
        handle->debug_print("tm1929: write fix brightness register failed.\n");           /* write fix brightness register failed */
       
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t tm1929_set_all_off(tm1929_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[18];
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    memset(buf, 0, sizeof(uint8_t) * 18);                                              /* set 0 */
    res = a_tm1929_iic_write(handle, TM1929_REG_FIXBRIT_LED0, buf, 18);                /* write fix brightness register */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("tm1929: write fix brightness register failed.\n");        /* write fix brightness register failed */
       
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t tm1929_set_all_on(tm1929_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[18];
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    memset(buf, 127, sizeof(uint8_t) * 18);                                            /* set 127 */
    res = a_tm1929_iic_write(handle, TM1929_REG_FIXBRIT_LED0, buf, 18);                /* write fix brightness register */
    if (res != 0)                                                                      /* check the result */
    {
        handle->debug_print("tm1929: write fix brightness register failed.\n");        /* write fix brightness register failed */
       
        return 1;                                                                      /* return error */
    }
    
    return 0;                                                                          /* success return 0 */
}

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
uint8_t tm1929_set_reg(tm1929_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_tm1929_iic_write(handle, reg, buf, len);                    /* write data */
    if (res != 0)                                                       /* check the result */
    {
        handle->debug_print("tm1929: write register failed.\n");        /* write register failed */
       
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a tm1929 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tm1929_info(tm1929_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(tm1929_info_t));                         /* initialize tm1929 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set maximum temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set minimal temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
