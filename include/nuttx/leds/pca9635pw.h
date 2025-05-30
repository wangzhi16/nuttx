/****************************************************************************
 * include/nuttx/leds/pca9635pw.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __INCLUDE_NUTTX_LEDS_PCA9635PW_H
#define __INCLUDE_NUTTX_LEDS_PCA9635PW_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/fs/ioctl.h>

/* Configuration
 * CONFIG_I2C - Enables support for I2C drivers
 * CONFIG_PCA9635PW - Enables support for the PCA9635PW driver
 */

#if defined(CONFIG_I2C) && defined(CONFIG_PCA9635PW)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* I2C definitions */

#define I2C_BUS_FREQ_HZ            (1000000)

/* PCA9635PW register addresses */

#define PCA9635PW_MODE_1           (0x00)                     /* Mode register 1 */
#define PCA9635PW_MODE_2           (0x01)                     /* Mode register 2 */
#define PCA9635PW_LED_0            (0x02)                     /* LED 0 brightness control */
#define PCA9635PW_LED_1            (PCA9635PW_LED_0 + 1)      /* LED 1 brightness control */
#define PCA9635PW_LED_2            (PCA9635PW_LED_0 + 2)      /* LED 2 brightness control */
#define PCA9635PW_LED_3            (PCA9635PW_LED_0 + 3)      /* LED 3 brightness control */
#define PCA9635PW_LED_4            (PCA9635PW_LED_0 + 4)      /* LED 4 brightness control */
#define PCA9635PW_LED_5            (PCA9635PW_LED_0 + 5)      /* LED 5 brightness control */
#define PCA9635PW_LED_6            (PCA9635PW_LED_0 + 6)      /* LED 6 brightness control */
#define PCA9635PW_LED_7            (PCA9635PW_LED_0 + 7)      /* LED 7 brightness control */
#define PCA9635PW_LED_8            (PCA9635PW_LED_0 + 8)      /* LED 8 brightness control */
#define PCA9635PW_LED_9            (PCA9635PW_LED_0 + 9)      /* LED 9 brightness control */
#define PCA9635PW_LED_10           (PCA9635PW_LED_0 + 10)     /* LED 10 brightness control */
#define PCA9635PW_LED_11           (PCA9635PW_LED_0 + 11)     /* LED 11 brightness control */
#define PCA9635PW_LED_12           (PCA9635PW_LED_0 + 12)     /* LED 12 brightness control */
#define PCA9635PW_LED_13           (PCA9635PW_LED_0 + 13)     /* LED 13 brightness control */
#define PCA9635PW_LED_14           (PCA9635PW_LED_0 + 14)     /* LED 14 brightness control */
#define PCA9635PW_LED_15           (PCA9635PW_LED_0 + 15)     /* LED 15 brightness control */
#define PCA9635PW_GRPPWM           (0x12)                     /* Group duty cycle control */
#define PCA9635PW_GRPFREQ          (0x13)                     /* group frequency */
#define PCA9635PW_LED_OUT_0        (0x14)                     /* LED output state 0 */
#define PCA9635PW_LED_OUT_1        (PCA9635PW_LED_OUT_0 + 1)  /* LED output state 1 */
#define PCA9635PW_LED_OUT_2        (PCA9635PW_LED_OUT_0 + 2)  /* LED output state 2 */
#define PCA9635PW_LED_OUT_3        (PCA9635PW_LED_OUT_0 + 3)  /* LED output state 3 */

/* PCA9635PW_MODE_1 bit definitions */

#define PCA9635PW_MODE_1_AI2       (1<<7)                     /* auto increment enable/disable */
#define PCA9635PW_MODE_1_AI1       (1<<6)                     /* auto increment bit 1 */
#define PCA9635PW_MODE_1_AI0       (1<<5)                     /* auto increment bit 0 */
#define PCA9635PW_MODE_1_SLEEP     (1<<4)                     /* low power mode/sleep enable/disable */
#define PCA9635PW_MODE_1_SUB1      (1<<3)                     /* PCA9635PW responds to I2C subaddress 1 enable/disable */
#define PCA9635PW_MODE_1_SUB2      (1<<2)                     /* PCA9635PW responds to I2C subaddress 2 enable/disable */
#define PCA9635PW_MODE_1_SUB3      (1<<1)                     /* PCA9635PW responds to I2C subaddress 3 enable/disable */
#define PCA9635PW_MODE_1_ALLCALL   (1<<0)                     /* PCA9635PW responds to led all call I2C address enable/disable */

/* PCA9635PW_MODE_2 bit definitions */

#define PCA9635PW_MODE_2_DMBLNK    (1<<5)                     /* group control dimming/blinking */
#define PCA9635PW_MODE_2_INVRT     (1<<4)                     /* output logic state inverted/not inverted */
#define PCA9635PW_MODE_2_OCH       (1<<3)                     /* output change on stop command/on ACK */
#define PCA9635PW_MODE_2_OUTDRV    (1<<2)                     /* outputs are configured with an open-drain-structure/totem-pole-structure */
#define PCA9635PW_MODE_2_OUTNE1    (1<<1)                     /* handling of outputs in dependency of !OE pin */
#define PCA9635PW_MODE_2_OUTNE0    (1<<0)                     /* handling of outputs in dependency of !OE pin */

/* PCA9635PW_LED_OUT_x register value definitions */

#define PCA9635PW_LED_OUT_X_MODE_0 (0x00)                     /* all led drivers are turned off */
#define PCA9635PW_LED_OUT_X_MODE_1 (0x55)                     /* all led drivers are fully turned on */
#define PCA9635PW_LED_OUT_X_MODE_2 (0xAA)                     /* all led drivers individual brightness can be controlled by their individual pwm registers */
#define PCA9635PW_LED_OUT_X_MODE_3 (0xFF)                     /* all led drivers individual brightness and group dimming/blinking can be controlled by their individual pwm registers and the GRPPWM register */

/* IOCTL commands */

#define PWMIOC_SETLED_BRIGHTNESS   _PWMIOC(1)                 /* Arg: pca9635pw_brightness_s * pointer */

/****************************************************************************
 * Public Types
 ****************************************************************************/

enum led_select_e
{
  LED_0 = PCA9635PW_LED_0,
  LED_1 = PCA9635PW_LED_1,
  LED_2 = PCA9635PW_LED_2,
  LED_3 = PCA9635PW_LED_3,
  LED_4 = PCA9635PW_LED_4,
  LED_5 = PCA9635PW_LED_5,
  LED_6 = PCA9635PW_LED_6,
  LED_7 = PCA9635PW_LED_7,
  LED_8 = PCA9635PW_LED_8,
  LED_9 = PCA9635PW_LED_9,
  LED_10 = PCA9635PW_LED_10,
  LED_11 = PCA9635PW_LED_11,
  LED_12 = PCA9635PW_LED_12,
  LED_13 = PCA9635PW_LED_13,
  LED_14 = PCA9635PW_LED_14,
  LED_15 = PCA9635PW_LED_15
};

/* This structure is used in an IOCTL command for setting the PWM of an
 * individual LED. The desired LED is selected by setting the 'led'
 * parameter accordingly whereas the 'led_pwm' field governs the brightness
 * of the selected LED.
 * A value of 0 (0x00) leads to a duty cycle of 0 % = LED off while a value
 * of 255 (0xFF) leads to a duty cycle of 99.6 % = Maximum brightness.
 */

struct pca9635pw_brightness_s
{
  enum led_select_e led;
  uint8_t brightness;
};

/****************************************************************************
 * Forward declarations
 ****************************************************************************/

struct i2c_master_s;

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: pca9635pw_register
 *
 * Description:
 *   Register the PCA9635PW device as 'devpath'
 *
 * Input Parameters:
 *   devpath - The full path to the driver to register. E.g., "/dev/leddrv0".
 *   i2c     - An instance of the I2C interface to use to communicate
 *             with the LM92.
 *   pca9635pw_i2c_addr
 *           - The I2C address of the PCA9635PW.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int pca9635pw_register(FAR const char *devpath, FAR struct i2c_master_s *i2c,
                       uint8_t const pca9635pw_i2c_addr);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* CONFIG_I2C && CONFIG_I2C_PCA9635PW */
#endif /* __INCLUDE_NUTTX_LEDS_PCA9635PW_H */
