/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define DRV_NAME        "gpio_pps"

#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/pps-gpio.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/irq.h>

#include <linux/string.h>

/* the module parameters */
static unsigned pin;
module_param(pin, uint, 17);
MODULE_PARM_DESC(pin, "gpio pin number for pps");

static bool afe;
module_param(afe, bool, false);
MODULE_PARM_DESC(afe, "assert falling edge");

static bool cc;
module_param(cc, bool, false);
MODULE_PARM_DESC(cc, "capture clear");

static struct pps_gpio_platform_data pps_gpio_info = {
    .assert_falling_edge = false,
    .capture_clear = false,
    .gpio_pin = 17,
    .gpio_label = "PPS",
};
static struct platform_device pps_gpio_device = {
    .name = "pps-gpio",
    .id = -1,
    .dev = { .platform_data = &pps_gpio_info },
};

static int __init gpio_config_init(void)
{
    pps_gpio_info.gpio_pin = pin;
    pps_gpio_info.assert_falling_edge = afe;
    pps_gpio_info.capture_clear = cc;
    platform_device_register(&pps_gpio_device);
    return 0;
}
module_init(gpio_config_init)

static void __exit gpio_config_exit(void)
{
	/* unregister devices */
    platform_device_unregister(&pps_gpio_device);
	/* and return */
}
module_exit(gpio_config_exit);

/* the module description */
MODULE_DESCRIPTION("bind gpio pin to pps");
MODULE_AUTHOR("tz1<tz@execpc.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);

