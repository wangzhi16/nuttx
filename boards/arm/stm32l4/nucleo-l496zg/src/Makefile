############################################################################
# boards/arm/stm32l4/nucleo-l496zg/src/Makefile
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.
#
############################################################################

include $(TOPDIR)/Make.defs

CSRCS = stm32_boot.c stm32_bringup.c

ifeq ($(CONFIG_ARCH_LEDS),y)
CSRCS += stm32_autoleds.c
else
CSRCS += stm32_userleds.c
endif

ifeq ($(CONFIG_ARCH_BUTTONS),y)
CSRCS += stm32_buttons.c
endif

ifeq ($(CONFIG_BOARDCTL),y)
CSRCS += stm32_appinitialize.c
ifeq ($(CONFIG_BOARDCTL_IOCTL),y)
CSRCS += stm32_ioctl.c
endif
endif

ifeq ($(CONFIG_SPI),y)
CSRCS += stm32_spi.c
endif

ifeq ($(CONFIG_ADC),y)
CSRCS += stm32_adc.c
  ifeq ($(CONFIG_STM32L4_DFSDM),y)
  CSRCS += stm32_dfsdm.c
  endif
endif

ifeq ($(CONFIG_DAC),y)
CSRCS += stm32_dac.c
endif

ifeq ($(CONFIG_MMCSD),y)
CSRCS += stm32_sdio.c
endif

ifeq ($(CONFIG_STM32L4_OTGFS),y)
CSRCS += stm32_usb.c
endif

ifeq ($(CONFIG_BOARDCTL_UNIQUEID),y)
CSRCS += stm32_uid.c
endif

ifneq ($(CONFIG_STM32_ETHMAC),y)
ifeq ($(CONFIG_NETDEVICES),y)
CSRCS += stm32_netinit.c
endif
endif

include $(TOPDIR)/boards/Board.mk
