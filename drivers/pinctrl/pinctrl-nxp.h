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


#ifndef __PINCTRL_NXP_H
#define __PINCTRL_NXP_H

#include <linux/kernel.h>

struct nxp_pinctrl_pio {
	void __iomem *membase;
	struct gpio_chip chip;
	int index;
	u32 iofn[32];
	u32 pins[32];
	int pin_num;
};

struct nxp_pinctrl {
	const char	*name;
	struct device *dev;
	struct pinctrl_dev *pctl_dev;
	struct nxp_pinctrl_pio *pio;
	int pio_num;
};

#define	chip_to_pinctrl(c)	container_of(chip, struct nxp_pinctrl_pio, chip)

#endif /* __PINCTRL_NXP_H */
