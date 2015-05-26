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
#include <linux/version.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/platform_device.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/of_platform.h>
#include <linux/clk-provider.h>

#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/pgtable.h>
#include <asm/system_misc.h>

/* nexell soc headers */
#include <nexell/platform.h>
#include <mach/iomap.h>

#ifdef	PB_IO_MAP
#undef	PB_IO_MAP
#endif

#define PB_IO_MAP(_n_, _v_, _p_, _s_, _t_) { \
	.virtual	= _v_,					\
	.pfn 		= __phys_to_pfn(_p_),	\
	.length 	= _s_, 					\
	.type 		= _t_ 					\
	},

static struct map_desc cpu_iomap_desc[] = {
	#include <mach/s5p6818_iomap.h>
};

extern void nxp_cpu_init(void);
extern void nxp_cpu_init_time(void);
extern void nxp_cpu_init_irq(void);
extern struct smp_operations nxp_smp_ops;

/*
 * 	cpu initialize and io/memory map.
 * 	procedure: fixup -> map_io -> init_irq -> timer init -> init_machine
 */
static void __init cpu_map_io(void)
{
	int i;

	for (i = 0; i<ARRAY_SIZE(cpu_iomap_desc); i++) {
		printk(KERN_INFO "CPU : iomap[%2d]: p 0x%08x -> v 0x%08x len=0x%x\n", i,
			(u_int)(cpu_iomap_desc[i].pfn<<12),	(u_int)(cpu_iomap_desc[i].virtual),
			(u_int)(cpu_iomap_desc[i].length));
	}

	/* make iotable */
	iotable_init(cpu_iomap_desc, ARRAY_SIZE(cpu_iomap_desc));
}

static void __init cpu_init_early(void)
{
	nxp_cpu_init();
}

static void __init cpu_init_machine(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

#if defined CONFIG_CMA && defined CONFIG_ION
#include <linux/memblock.h>
#include <linux/cma.h>

static void __init nxp_cma_region_reserve(struct cma_region *regions, const char *map)
{
    struct cma_region *reg;
    phys_addr_t paddr_last = 0xFFFFFFFF;

    for (reg = regions; reg->size != 0; reg++) {
        phys_addr_t paddr;

        if (!IS_ALIGNED(reg->size, PAGE_SIZE)) {
            pr_debug("NXP/CMA: size of '%s' is NOT page-aligned\n", reg->name);
            reg->size = PAGE_ALIGN(reg->size);
        }

        if (reg->reserved) {
            pr_err("NXP/CMA: '%s' already reserved\n", reg->name);
            continue;
        }

        if (reg->alignment) {
            if ((reg->alignment & ~PAGE_MASK) ||
                (reg->alignment & ~reg->alignment)) {
                pr_err("NXP/CMA: failed to reserve '%s': "
                        "incorrect alignment 0x%08x.\n",
                        reg->name, reg->alignment);
                continue;
            }
        } else {
            reg->alignment = PAGE_SIZE;
        }

        if (reg->start) {
            if (!memblock_is_region_reserved(reg->start, reg->size)
                && (memblock_reserve(reg->start, reg->size) == 0)) {
                reg->reserved = 1;
            } else {
                pr_err("NXP/CMA: failed to reserve '%s'\n", reg->name);
            }

        } else {
            paddr = memblock_find_in_range(0, MEMBLOCK_ALLOC_ACCESSIBLE,
                    reg->size, reg->alignment);
            if (paddr) {
                if (memblock_reserve(paddr, reg->size)) {
                    pr_err("NXP/CMA: failed to reserve '%s': memblock_reserve() failed\n",
                            reg->name);
                    continue;
                }

                reg->start = paddr;
                reg->reserved = 1;
            } else {
                pr_err("NXP/CMA: No free space in memory for '%s': size(%d)\n",
                        reg->name, reg->size);
            }
        }

        if (reg->reserved) {
            pr_debug("NXP/CMA: "
                    "Reserved 0x%08x/0x%08x for '%s'\n",
                    reg->start, reg->size, reg->name);
            printk("NXP/CMA: "
                    "Reserved 0x%08x/0x%08x for '%s'\n",
                    reg->start, reg->size, reg->name);

            if (0 == cma_early_region_register(reg)) {
                paddr_last = min(paddr, paddr_last);
                pr_debug("NXP/CMA: success register cma region for '%s'\n",
                        reg->name);
                printk("NXP/CMA: success register cma region for '%s'\n",
                        reg->name);
            } else {
                pr_err("NXP/CMA: failed to cma_early_region_register for '%s'\n",
                        reg->name);
                memblock_free(reg->start, reg->size);
            }
        }
    }

    if (map) {
        cma_set_defaults(NULL, map);
    }
}

static void __init nxp_reserve_mem(void)
{
    static struct cma_region regions[] = {
        {
            .name = "ion",
#ifdef CONFIG_ION_NXP_CONTIGHEAP_SIZE
            .size = CONFIG_ION_NXP_CONTIGHEAP_SIZE * SZ_1K,
#else
			.size = 0,
#endif
            {
                .alignment = PAGE_SIZE,
            }
        },
        {
            .size = 0
        }
    };

    static const char map[] __initconst =
        "*=ion;"
        "ion-nxp=ion;"
        "nx_vpu=ion;";

#ifdef CONFIG_ION_NXP_CONTIGHEAP_SIZE
    printk("%s: reserve CMA: size %d\n", __func__, CONFIG_ION_NXP_CONTIGHEAP_SIZE * SZ_1K);
#endif
    nxp_cma_region_reserve(regions, map);
}

static void __init cpu_mem_reserve(void)
{
#ifdef CONFIG_CMA
extern void nxp_reserve_mem(void);
	nxp_reserve_mem();
#endif

#ifdef CONFIG_ANDROID_RAM_CONSOLE
	persistent_ram_console_reserve();
#endif
}
#endif

/*
 * Maintainer: Nexell Co., Ltd.
 */
static const char * const cpu_dt_compat[] = {
    "Nexell,s5p6818",
    NULL
};

DT_MACHINE_START(S5P6818, "s5p6818")
	.atag_offset	= 0x00000100,
	.nr				= 6818,
	.smp			= smp_ops(nxp_smp_ops),
	.map_io			= cpu_map_io,
	.init_early		= cpu_init_early,
	.init_machine	= cpu_init_machine,
	.dt_compat  	= cpu_dt_compat,
#if defined CONFIG_CMA && defined CONFIG_ION
    .reserve        = cpu_mem_reserve,
#endif
MACHINE_END
