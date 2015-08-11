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
#ifndef __PLAT_PM_H__
#define __PLAT_PM_H__

#include <linux/suspend.h>

struct pm_suspend_ops {
	int  (*valid)		(suspend_state_t state);	/* before driver suspend */
	int  (*begin)		(suspend_state_t state);	/* before driver suspend */
	int  (*prepare)		(void);						/* after driver suspend */
	int  (*enter) 		(suspend_state_t state);	/* enter suspend */
	int  (*poweroff)	(void);						/* before cpu power off */
	void (*poweron)		(void);						/* after cpu power on */
	void (*finish)		(void);						/* before driver resume */
	void (*end)			(void);						/* after driver resume */
};

struct pm_suspend_sign {
	u32 resume;
	u32 signature;
	u32 crc_addr;
	u32 crc_size;
	u32 crc_ret;
};

extern void pm_pre_ops_register(struct pm_suspend_ops *pm_ops);
extern void (*pm_suspend_signatrue)(struct pm_suspend_sign*, int);

#endif /* __PLAT_PM_H__ */