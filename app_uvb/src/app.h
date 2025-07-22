/*
 * Copyright (c) 2025 Nordic Semiconductor ASA.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NORDIC_USBH_TESTS_APP_H
#define NORDIC_USBH_TESTS_APP_H

#include <stdint.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/usb/usbh.h>

struct usbd_context *app_usbd_init_device(void);
struct usbh_contex *app_usbh_init_controller(void);

#endif /* NORDIC_USBH_TESTS_APP_H */
