/*
 * (C) Copyright 2009
 * jung hyun kim, Nexell Co, <jhkim@nexell.co.kr>
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

#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/pinctrl/consumer.h>
#include <linux/pinctrl/machine.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/pinctrl/pinconf-generic.h>
#include <linux/pinctrl/pinmux.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#include <nexell/platform.h>
#include <nexell/soc-s5pxx18.h>

#include "core.h"
#include "pinctrl-nxp.h"

/*
#define	pr_debug	printk
*/

#define	PIN_FN_SIZE		(4)

static const struct pinctrl_pin_desc s5p6818_pins[] = {
	PINCTRL_PIN(  0, "PA0"),
	PINCTRL_PIN(  1, "PA1"),
	PINCTRL_PIN(  2, "PA2"),
	PINCTRL_PIN(  3, "PA3"),
	PINCTRL_PIN(  4, "PA4"),
	PINCTRL_PIN(  5, "PA5"),
	PINCTRL_PIN(  6, "PA6"),
	PINCTRL_PIN(  7, "PA7"),
	PINCTRL_PIN(  8, "PA8"),
	PINCTRL_PIN(  9, "PA9"),
	PINCTRL_PIN( 10, "PA10"),
	PINCTRL_PIN( 11, "PA11"),
	PINCTRL_PIN( 12, "PA12"),
	PINCTRL_PIN( 13, "PA13"),
	PINCTRL_PIN( 14, "PA14"),
	PINCTRL_PIN( 15, "PA15"),
	PINCTRL_PIN( 16, "PA16"),
	PINCTRL_PIN( 17, "PA17"),
	PINCTRL_PIN( 18, "PA18"),
	PINCTRL_PIN( 19, "PA19"),
	PINCTRL_PIN( 20, "PA20"),
	PINCTRL_PIN( 21, "PA21"),
	PINCTRL_PIN( 22, "PA22"),
	PINCTRL_PIN( 23, "PA23"),
	PINCTRL_PIN( 24, "PA24"),
	PINCTRL_PIN( 25, "PA25"),
	PINCTRL_PIN( 26, "PA26"),
	PINCTRL_PIN( 27, "PA27"),
	PINCTRL_PIN( 28, "PA28"),
	PINCTRL_PIN( 29, "PA29"),
	PINCTRL_PIN( 30, "PA30"),
	PINCTRL_PIN( 31, "PA31"),
	PINCTRL_PIN( 32, "PB0"),
	PINCTRL_PIN( 33, "PB1"),
	PINCTRL_PIN( 34, "PB2"),
	PINCTRL_PIN( 35, "PB3"),
	PINCTRL_PIN( 36, "PB4"),
	PINCTRL_PIN( 37, "PB5"),
	PINCTRL_PIN( 38, "PB6"),
	PINCTRL_PIN( 39, "PB7"),
	PINCTRL_PIN( 40, "PB8"),
	PINCTRL_PIN( 41, "PB9"),
	PINCTRL_PIN( 42, "PB10"),
	PINCTRL_PIN( 43, "PB11"),
	PINCTRL_PIN( 44, "PB12"),
	PINCTRL_PIN( 45, "PB13"),
	PINCTRL_PIN( 46, "PB14"),
	PINCTRL_PIN( 47, "PB15"),
	PINCTRL_PIN( 48, "PB16"),
	PINCTRL_PIN( 49, "PB17"),
	PINCTRL_PIN( 50, "PB18"),
	PINCTRL_PIN( 51, "PB19"),
	PINCTRL_PIN( 52, "PB20"),
	PINCTRL_PIN( 53, "PB21"),
	PINCTRL_PIN( 54, "PB22"),
	PINCTRL_PIN( 55, "PB23"),
	PINCTRL_PIN( 56, "PB24"),
	PINCTRL_PIN( 57, "PB25"),
	PINCTRL_PIN( 58, "PB26"),
	PINCTRL_PIN( 59, "PB27"),
	PINCTRL_PIN( 60, "PB28"),
	PINCTRL_PIN( 61, "PB29"),
	PINCTRL_PIN( 62, "PB30"),
	PINCTRL_PIN( 63, "PB31"),
	PINCTRL_PIN( 64, "PC0"),
	PINCTRL_PIN( 65, "PC1"),
	PINCTRL_PIN( 66, "PC2"),
	PINCTRL_PIN( 67, "PC3"),
	PINCTRL_PIN( 68, "PC4"),
	PINCTRL_PIN( 69, "PC5"),
	PINCTRL_PIN( 70, "PC6"),
	PINCTRL_PIN( 71, "PC7"),
	PINCTRL_PIN( 72, "PC8"),
	PINCTRL_PIN( 73, "PC9"),
	PINCTRL_PIN( 74, "PC10"),
	PINCTRL_PIN( 75, "PC11"),
	PINCTRL_PIN( 76, "PC12"),
	PINCTRL_PIN( 77, "PC13"),
	PINCTRL_PIN( 78, "PC14"),
	PINCTRL_PIN( 79, "PC15"),
	PINCTRL_PIN( 80, "PC16"),
	PINCTRL_PIN( 81, "PC17"),
	PINCTRL_PIN( 82, "PC18"),
	PINCTRL_PIN( 83, "PC19"),
	PINCTRL_PIN( 84, "PC20"),
	PINCTRL_PIN( 85, "PC21"),
	PINCTRL_PIN( 86, "PC22"),
	PINCTRL_PIN( 87, "PC23"),
	PINCTRL_PIN( 88, "PC24"),
	PINCTRL_PIN( 89, "PC25"),
	PINCTRL_PIN( 90, "PC26"),
	PINCTRL_PIN( 91, "PC27"),
	PINCTRL_PIN( 92, "PC28"),
	PINCTRL_PIN( 93, "PC29"),
	PINCTRL_PIN( 94, "PC30"),
	PINCTRL_PIN( 95, "PC31"),
	PINCTRL_PIN( 96, "PD0"),
	PINCTRL_PIN( 97, "PD1"),
	PINCTRL_PIN( 98, "PD2"),
	PINCTRL_PIN( 99, "PD3"),
	PINCTRL_PIN(100, "PD4"),
	PINCTRL_PIN(101, "PD5"),
	PINCTRL_PIN(102, "PD6"),
	PINCTRL_PIN(103, "PD7"),
	PINCTRL_PIN(104, "PD8"),
	PINCTRL_PIN(105, "PD9"),
	PINCTRL_PIN(106, "PD10"),
	PINCTRL_PIN(107, "PD11"),
	PINCTRL_PIN(108, "PD12"),
	PINCTRL_PIN(109, "PD13"),
	PINCTRL_PIN(110, "PD14"),
	PINCTRL_PIN(111, "PD15"),
	PINCTRL_PIN(112, "PD16"),
	PINCTRL_PIN(113, "PD17"),
	PINCTRL_PIN(114, "PD18"),
	PINCTRL_PIN(115, "PD19"),
	PINCTRL_PIN(116, "PD20"),
	PINCTRL_PIN(117, "PD21"),
	PINCTRL_PIN(118, "PD22"),
	PINCTRL_PIN(119, "PD23"),
	PINCTRL_PIN(120, "PD24"),
	PINCTRL_PIN(121, "PD25"),
	PINCTRL_PIN(122, "PD26"),
	PINCTRL_PIN(123, "PD27"),
	PINCTRL_PIN(124, "PD28"),
	PINCTRL_PIN(125, "PD29"),
	PINCTRL_PIN(126, "PD30"),
	PINCTRL_PIN(127, "PD31"),
	PINCTRL_PIN(128, "PE0"),
	PINCTRL_PIN(129, "PE1"),
	PINCTRL_PIN(130, "PE2"),
	PINCTRL_PIN(131, "PE3"),
	PINCTRL_PIN(132, "PE4"),
	PINCTRL_PIN(133, "PE5"),
	PINCTRL_PIN(134, "PE6"),
	PINCTRL_PIN(135, "PE7"),
	PINCTRL_PIN(136, "PE8"),
	PINCTRL_PIN(137, "PE9"),
	PINCTRL_PIN(138, "PE10"),
	PINCTRL_PIN(139, "PE11"),
	PINCTRL_PIN(140, "PE12"),
	PINCTRL_PIN(141, "PE13"),
	PINCTRL_PIN(142, "PE14"),
	PINCTRL_PIN(143, "PE15"),
	PINCTRL_PIN(144, "PE16"),
	PINCTRL_PIN(145, "PE17"),
	PINCTRL_PIN(146, "PE18"),
	PINCTRL_PIN(147, "PE19"),
	PINCTRL_PIN(148, "PE20"),
	PINCTRL_PIN(149, "PE21"),
	PINCTRL_PIN(150, "PE22"),
	PINCTRL_PIN(151, "PE23"),
	PINCTRL_PIN(152, "PE24"),
	PINCTRL_PIN(153, "PE25"),
	PINCTRL_PIN(154, "PE26"),
	PINCTRL_PIN(155, "PE27"),
	PINCTRL_PIN(156, "PE28"),
	PINCTRL_PIN(157, "PE29"),
	PINCTRL_PIN(158, "PE30"),
	PINCTRL_PIN(159, "PE31"),
	PINCTRL_PIN(160, "AL0"),
	PINCTRL_PIN(161, "AL1"),
	PINCTRL_PIN(162, "AL2"),
	PINCTRL_PIN(163, "AL3"),
	PINCTRL_PIN(164, "AL4"),
	PINCTRL_PIN(165, "AL5"),
};

static const char *pin_name[] = {
	"GPIOA", "GPIOB", "GPIOC", "GPIOD", "GPIOE", "ALIVE"
};

static struct pinctrl_desc nxp_pinctrl_desc = {
 	.name 	= "gpio",
 	.pins 	= s5p6818_pins,
 	.npins 	= ARRAY_SIZE(s5p6818_pins),
 	.owner 	= THIS_MODULE,
};

static int nxp_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct nxp_pinctrl_pio *pio = chip_to_pinctrl(chip);
	int pin = pio->index * GPIO_NUM_PER_BANK + offset;
	int fn = GET_GPIO_ALTFUNC(pio->index, offset);

	pr_debug("gpio_request: %s.%2d=%3d]\n", pin_name[pio->index], offset, pin);

	nxp_soc_gpio_set_io_func(pin, fn);
	return 0;
}

static int nxp_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct nxp_pinctrl_pio *pio = chip_to_pinctrl(chip);
	int pin = pio->index * GPIO_NUM_PER_BANK + offset;
	int irq = pin + IRQ_GPIO_START;

	pr_debug("gpio_to_irq: %s.%2d=%3d, irq=%d\n",
		pin_name[pio->index], offset, pin, irq);
	return irq;
}

static int nxp_gpio_direction_input(struct gpio_chip *chip,
						unsigned offset)
{
	struct nxp_pinctrl_pio *pio = chip_to_pinctrl(chip);
	int pin = pio->index * GPIO_NUM_PER_BANK + offset;
	int fn = GET_GPIO_ALTFUNC(pio->index, offset);

	pr_debug("direction_input: %s.%2d=%3d\n",
		pin_name[pio->index], offset, pin);

	nxp_soc_gpio_set_io_func(pin, fn);
	nxp_soc_gpio_set_io_dir(pin, 0);

	return 0;
}

static int nxp_gpio_direction_output(struct gpio_chip *chip,
						unsigned offset, int value)
{
	struct nxp_pinctrl_pio *pio = chip_to_pinctrl(chip);
	int pin = (pio->index * GPIO_NUM_PER_BANK) + offset;
	int fn = GET_GPIO_ALTFUNC(pio->index, offset);

	pr_debug("direction_output: %s.%2d=%3d, val=%d\n",
		pin_name[pio->index], offset, pin, value);

	nxp_soc_gpio_set_io_func(pin, fn);
	nxp_soc_gpio_set_out_value(pin, value);
	nxp_soc_gpio_set_io_dir(pin, 1);

	return 0;
}

static int nxp_gpio_get_value(struct gpio_chip *chip, unsigned offset)
{
	struct nxp_pinctrl_pio *pio = chip_to_pinctrl(chip);
	int pin = pio->index * GPIO_NUM_PER_BANK + offset;

	pr_debug("get_value: %s.%2d=%3d\n", pin_name[pio->index], offset, pin);

	return nxp_soc_gpio_get_in_value(pin);
}

static void nxp_gpio_set_value(struct gpio_chip *chip,
					unsigned offset, int value)
{
	struct nxp_pinctrl_pio *pio = chip_to_pinctrl(chip);
	int pin = pio->index * GPIO_NUM_PER_BANK + offset;

	nxp_soc_gpio_set_io_dir(pin, 1);
	nxp_soc_gpio_set_out_value(pin, value);

	pr_debug("set_value: %s.%2d=%3d, val=%d\n",
		pin_name[pio->index], offset, pin, value);
}

static struct of_device_id nxp_pinctrl_match[] = {
	{ .compatible = "nexell,nxp-pinctrl", .data = (void *)&nxp_pinctrl_desc },
	{}
};
MODULE_DEVICE_TABLE(of, nxp_pinctrl_match);

static void nxp_pinctrl_pio_setup(struct nxp_pinctrl_pio *pio)
{
	int idx = pio->index, pin = 0;

	NX_GPIO_ClearInterruptPendingAll(idx);

	for (pin = 0; pio->pin_num > pin; pin++) {
		int io = pio->pins[pin], alt = PAD_GET_FUNC(io);
		int mod = PAD_GET_MODE(io), lv = PAD_GET_LEVEL(io);
		int str = PAD_GET_STRENGTH(io), plup = PAD_GET_PULLUP(io);

		switch (alt) {
		case PAD_GET_FUNC(PAD_FUNC_ALT0): alt = NX_GPIO_PADFUNC_0;	break;
		case PAD_GET_FUNC(PAD_FUNC_ALT1): alt = NX_GPIO_PADFUNC_1;	break;
		case PAD_GET_FUNC(PAD_FUNC_ALT2): alt = NX_GPIO_PADFUNC_2;	break;
		case PAD_GET_FUNC(PAD_FUNC_ALT3): alt = NX_GPIO_PADFUNC_3;	break;
		default: pr_err("Error, unknown alt (%d.%02d=%d)\n", idx, pin, alt);
			continue;
		}

		NX_GPIO_SetPadFunction(idx, pin, alt);
		NX_GPIO_SetOutputEnable(idx, pin,
				(mod == PAD_GET_MODE(PAD_MODE_OUT) ? CTRUE : CFALSE));
		NX_GPIO_SetOutputValue(idx, pin,  (lv ? CTRUE : CFALSE));
		NX_GPIO_SetInterruptMode(idx, pin, lv);
		NX_GPIO_SetPullEnable(idx, pin, (NX_GPIO_PULL)plup);
		NX_GPIO_SetDriveStrength(idx, pin, (NX_GPIO_DRVSTRENGTH)str); /* pad strength */

		pr_debug("[Gpio %d.%2d: DIR %s, ALT %d, Level %s, Pull %s, Str %d]\n",
			idx, pin, mod == PAD_GET_MODE(PAD_MODE_OUT)?"OUT":" IN",
			alt, lv?"H":"L", plup==0?" DN":(plup==1?" UP":"OFF"), str);
	}
}

static void nxp_pinctrl_alive_setup(struct nxp_pinctrl_pio *pio)
{
	int pin = 0;

	for ( ; pio->pin_num > pin; pin++) {
		int io = pio->pins[pin], mod = PAD_GET_MODE(io);
		int lv = PAD_GET_LEVEL(io), plup = PAD_GET_PULLUP(io);
		int det = 0;

		NX_ALIVE_ClearInterruptPending(pin);
		NX_ALIVE_SetOutputEnable(pin, (mod == PAD_GET_MODE(PAD_MODE_OUT) ? CTRUE : CFALSE));
		NX_ALIVE_SetOutputValue (pin, lv);
		NX_ALIVE_SetPullUpEnable(pin, (plup & 1 ? CTRUE : CFALSE));

		for (det = 0; 6 > det; det++) {
			mod == PAD_GET_MODE(PAD_MODE_INT) ?
			NX_ALIVE_SetDetectMode(det, pin, (lv == det ? CTRUE : CFALSE)) :
			NX_ALIVE_SetDetectMode(det, pin, CFALSE);
		}
		NX_ALIVE_SetDetectEnable(pin, (mod == PAD_MODE_INT ? CTRUE : CFALSE));

		pr_debug("[ALive%d: DIR %s, evel %s, Pull %s]\n",
			pin, mod == PAD_GET_MODE(PAD_MODE_OUT)?"OUT":" IN",
			lv?"H":"L", lv==0?" DN": (lv==1?" UP":"OFF"));
	}
}

static int nxp_pinctrl_probe_dt(struct platform_device *pdev,
					struct nxp_pinctrl *pctl)
{
	struct device_node *np = pdev->dev.of_node;
	struct device_node *child;
	struct gpio_chip *chip;
	struct nxp_pinctrl_pio *pio;
	const __be32 *list;
	u32 *pin;
	int num, size;
	int ret = 0, i = 0, n = 0;

	num = of_get_child_count(np);
	if (0 >= num) {
		dev_err(&pdev->dev, "no functions defined\n");
		return -EINVAL;
	}

	pio = devm_kzalloc(&pdev->dev, sizeof(*pio)*num, GFP_KERNEL);
	if (!pio)
		return -ENOMEM;

	for_each_child_of_node(np, child) {
		list = of_get_property(child, "pin,functions", &size);
		size /= PIN_FN_SIZE;

		if (!list ||!size)
			continue;

		pio->membase = of_iomap(child, 0);
		pio->pin_num = size;
		pio->index = n;
		pin = pio->pins;

		for (i = 0; size > i; i++)
			pin[i] = be32_to_cpu(*list++);

		if (!of_node_cmp(child->type, "gpio"))
			nxp_pinctrl_pio_setup(pio);
		else if (!of_node_cmp(child->type, "alive"))
			nxp_pinctrl_alive_setup(pio);

		chip = &pio->chip;

		chip->request = nxp_gpio_request;
		chip->to_irq = nxp_gpio_to_irq;
		chip->direction_input = nxp_gpio_direction_input;
		chip->direction_output = nxp_gpio_direction_output;
		chip->get = nxp_gpio_get_value;
		chip->set = nxp_gpio_set_value;
		chip->ngpio = size;
		chip->label = dev_name(&pdev->dev);
		chip->dev = &pdev->dev;
		chip->owner = THIS_MODULE;
		chip->base = pio->index * GPIO_NUM_PER_BANK;

		ret = gpiochip_add(chip);
		if (ret) {
			devm_kfree(&pdev->dev, pio);
			return ret;
		}

		pio++, n++;
	}

	pctl->pio = pio;
	pctl->pio_num = num;
	return 0;
}

static int nxp_pinctrl_probe(struct platform_device *pdev)
{
	struct nxp_pinctrl *pctl;
	struct pinctrl_dev *pctl_dev;
	int ret = 0;

	pctl = devm_kzalloc(&pdev->dev, sizeof(*pctl), GFP_KERNEL);
	if (!pctl)
		return -ENOMEM;

	ret = nxp_pinctrl_probe_dt(pdev, pctl);
	if (0 > ret) {
		devm_kfree(&pdev->dev, pctl);
		return ret;
	}

 	pctl_dev = pinctrl_register(&nxp_pinctrl_desc, &pdev->dev, pctl);
 	if (IS_ERR(pctl)) {
 		pr_err("could not register foo pin driver\n");
 		devm_kfree(&pdev->dev, pctl);
		return -EINVAL;
	}

	pctl->pctl_dev = pctl_dev;
	platform_set_drvdata(pdev, pctl);

	return ret;
}

static struct platform_driver nxp_pinctrl_driver = {
	.probe = nxp_pinctrl_probe,
	.driver = {
		.name = "nxp-pinctrl",
		.owner = THIS_MODULE,
		.of_match_table = nxp_pinctrl_match,
	},
};

static int __init nxp_pinctrl_init(void)
{
	return platform_driver_register(&nxp_pinctrl_driver);
}
subsys_initcall(nxp_pinctrl_init);

MODULE_DESCRIPTION("SLsiAP pinctrl driver");
MODULE_LICENSE("GPL");
