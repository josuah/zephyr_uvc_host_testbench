/*
 * Copyright (c) 2025 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/usb/usbh.h>

LOG_MODULE_REGISTER(app_main);

#include "app.h"

int main(void)
{
	struct usbd_context *usbd_ctx;
	struct usbh_contex *usbh_ctx;

	usbd_ctx = app_usbd_init_device();
	if (usbd_ctx == NULL) {
    		LOG_ERR("Failed to initialize USB Device contexts");
    		return 0;
	}

	usbh_ctx = app_usbh_init_controller();
	if (usbh_ctx == NULL) {
    		LOG_ERR("Failed to initialize USB Host controller");
    		return 0;
	}

	return 0;
}
