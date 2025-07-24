/*
 * Copyright (c) 2025 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/usb/usbh.h>
#include <zephyr/usb/class/usbd_uvc.h>

#include "usbh_device.h"
#include "usbh_ch9.h"

LOG_MODULE_REGISTER(app_main, LOG_LEVEL_INF);

#include "app.h"

#define APP_USBH_CLASS_DESC_MAX_SIZE 512

int usbh_class_init(struct usb_device *udev)
{
	const size_t len = APP_USBH_CLASS_DESC_MAX_SIZE;
	struct net_buf *buf;
	int ret;

	buf = usbh_xfer_buf_alloc(udev, len);
	if (buf == NULL) {
    		LOG_ERR("Failed to allocate a host transfer buffer");
		return -ENOMEM;
	}

	ret = usbh_req_desc(udev, USB_DESC_DEVICE, 0, 0, len, buf);
	if (ret != 0) {
    		LOG_ERR("Failed to request descriptor");
		return ret;
	}

	LOG_HEXDUMP_INF(buf->data, buf->len, "buf");

	return 0;
}

const struct device *const uvc_dev = DEVICE_DT_GET(DT_NODELABEL(uvc_device));
const struct device *const video_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_camera));

int main(void)
{
	struct usbd_context *app_usbd;
	struct usbh_contex *app_usbh;
	int ret;

	uvc_set_video_dev(uvc_dev, video_dev);

	/* Enable the virtual USB device and virtual USB host so they can
	 * communicate together
	 */

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

	ret = usbh_enable(app_usbh);
	if (ret != 0) {
		LOG_ERR("Failed to enable USB Host");
		return 0;
	}

	ret = usbd_enable(app_usbd);
	if (ret != 0) {
		LOG_ERR("Failed to enable USB Device");
		return 0;
	}

	return 0;
}
