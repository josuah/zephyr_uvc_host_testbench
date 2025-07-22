/*
 * Copyright (c) 2025 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/usb/usbh.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(usbh_app_config);

USBH_CONTROLLER_DEFINE(app_usbh,
		       DEVICE_DT_GET(DT_NODELABEL(virtual_uhc0)));

struct usbh_contex *app_usbh_init_controller(void)
{
	int err;

	err = usbh_init(&app_usbh);
	if (err) {
		LOG_ERR("Failed to initialize host support");
		return NULL;
	}

	return &app_usbh;
}
