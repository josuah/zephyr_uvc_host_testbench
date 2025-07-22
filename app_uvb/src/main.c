/*
 * Copyright (c) 2025 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/usb/usbh.h>

LOG_MODULE_REGISTER(app_main, LOG_LEVEL_INF);

#include "app.h"

USBH_DEFINE_CLASS(class);

int app_class_request(struct usbh_contex *const uhs_ctx,
		struct uhc_transfer *const xfer, int err)
{
	LOG_INF("Request completion event handler");
	return 0;
}

int app_class_connected(struct usbh_contex *const uhs_ctx)
{
	LOG_INF("Device connected handler");
	return 0;
}

int app_class_removed(struct usbh_contex *const uhs_ctx)
{
	LOG_INF("Device removed handler");
	return 0;
}

int app_class_rwup(struct usbh_contex *const uhs_ctx)
{
	LOG_INF("Bus remote wakeup handler");
	return 0;
}

int app_class_suspended(struct usbh_contex *const uhs_ctx)
{
	LOG_INF("Bus suspended handler");
	return 0;
}

int app_class_resumed(struct usbh_contex *const uhs_ctx)
{
	LOG_INF("Bus resumed handler");
	return 0;
}

int main(void)
{
	struct usbd_context *app_usbd;
	struct usbh_contex *app_usbh;
	int ret;

	class.request = app_class_request;
	class.connected = app_class_connected;
	class.removed = app_class_removed;
	class.rwup = app_class_rwup;
	class.suspended = app_class_suspended;
	class.resumed = app_class_resumed;

	app_usbd = app_usbd_init_device();
	if (app_usbd == NULL) {
		LOG_ERR("Failed to initialize USB Device contexts");
		return 0;
	}

	app_usbh = app_usbh_init_controller();
	if (app_usbh == NULL) {
		LOG_ERR("Failed to initialize USB Host controller");
		return 0;
	}

	ret = usbd_enable(app_usbd);
	if (ret != 0) {
		LOG_ERR("Failed to enable USB Device");
		return 0;
	}

	ret = usbh_enable(app_usbh);
	if (ret != 0) {
		LOG_ERR("Failed to enable USB Host");
		return 0;
	}

	return 0;
}
