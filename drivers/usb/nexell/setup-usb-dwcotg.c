/*---------------------------------------------------------------------------------------
 * USB OTG Host or Gadget
 */

#include <linux/delay.h>
#include <asm/io.h>
#include <linux/usb/ch9.h>

#include <nexell/platform.h>

#define SOC_PA_HSOTG        PHYS_BASE_HSOTG
#define SOC_VA_HSOTG        IO_ADDRESS(SOC_PA_HSOTG)

#define SOC_PA_RSTCON       PHYS_BASE_RSTCON
#define SOC_VA_RSTCON       IO_ADDRESS(SOC_PA_RSTCON)

#define SOC_PA_TIEOFF       PHYS_BASE_TIEOFF
#define SOC_VA_TIEOFF       IO_ADDRESS(SOC_PA_TIEOFF)

void otg_clk_enable(void)
{
#if 0
    struct clk *hsotg_clk;

    // Clock control
    hsotg_clk = clk_get(NULL, DEV_NAME_USB2HOST);
    if (hsotg_clk)
        clk_enable(hsotg_clk);
#endif
}
EXPORT_SYMBOL(otg_clk_enable);

void otg_clk_disable(void)
{
#if 0
    struct clk *hsotg_clk;

    // Clock control
    hsotg_clk = clk_get(NULL, DEV_NAME_USB2HOST);
    if (hsotg_clk)
        clk_disable(hsotg_clk);
#endif
}
EXPORT_SYMBOL(otg_clk_disable);

/* Initializes OTG Phy. */
void otg_phy_init(void)
{
    u32 temp;

    pm_dbgout("+%s\n", __func__);

    writel(readl((void *)(SOC_VA_RSTCON + 0x3C)) & ~0xF800, (void *)(SOC_VA_RSTCON + 0x3C));

    // 1. Release otg common reset
    writel(readl((void *)(SOC_VA_RSTCON + 0x04)) & ~(1<<25), (void *)(SOC_VA_RSTCON + 0x04));     // reset on
    udelay(10);
    writel(readl((void *)(SOC_VA_RSTCON + 0x04)) |  (1<<25), (void *)(SOC_VA_RSTCON + 0x04));     // reset off
    udelay(10);

    // 1-1. VBUS reconfig - Over current Issue
#if 1
    temp  = readl((void *)(SOC_VA_TIEOFF + 0x38)) & ~(0x7<<23);
#if defined(CFG_OTG_OVC_VALUE)
    temp |= (CFG_OTG_OVC_VALUE << 23);
#else
//    temp |= (0x3<<23);
    temp |= (0x0<<23);
#endif
    writel(temp, (void *)(SOC_VA_TIEOFF + 0x38));
#endif

    // 2. Program scale mode to real mode
    writel(readl((void *)(SOC_VA_TIEOFF + 0x30)) & ~(3<<0), (void *)(SOC_VA_TIEOFF + 0x30));

    // 3. Select word interface and enable word interface selection
#if 0
    writel(readl((void *)(SOC_VA_TIEOFF + 0x38)) & ~(3<<8), (void *)(SOC_VA_TIEOFF + 0x38));
    writel(readl((void *)(SOC_VA_TIEOFF + 0x38)) |  (1<<8), (void *)(SOC_VA_TIEOFF + 0x38));        // 2'b01 8bit, 2'b11 16bit word
#else
    writel(readl((void *)(SOC_VA_TIEOFF + 0x38)) |  (3<<8), (void *)(SOC_VA_TIEOFF + 0x38));        // 2'b01 8bit, 2'b11 16bit word
#endif


    // 4. Select VBUS
//    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) |  (3<<24), (void *)(SOC_VA_TIEOFF + 0x34));   /* Select VBUS 3.3V */
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) & ~(3<<24), (void *)(SOC_VA_TIEOFF + 0x34));   /* Select VBUS 5V */

    // 5. POR of PHY
#if 0
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) |  (3<<7), (void *)(SOC_VA_TIEOFF + 0x34));
#else
    temp    = readl((void *)(SOC_VA_TIEOFF + 0x34));
    temp   &= ~(3<<7);
    temp   |=  (1<<7);
    writel(temp, (void *)(SOC_VA_TIEOFF + 0x34));
    udelay(1);
    temp   |=  (3<<7);
    writel(temp, (void *)(SOC_VA_TIEOFF + 0x34));
    udelay(1);
    temp   &= ~(2<<7);
    writel(temp, (void *)(SOC_VA_TIEOFF + 0x34));
#endif
    udelay(10); // 40us delay need.

    // 6. UTMI reset
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) | (1<<3), (void *)(SOC_VA_TIEOFF + 0x34));
    udelay(1);  // 10 clock need

    // 7. AHB reset
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) | (1<<2), (void *)(SOC_VA_TIEOFF + 0x34));
    udelay(1);  // 10 clock need
}
EXPORT_SYMBOL(otg_phy_init);

void otg_phy_off(void)
{
    pm_dbgout("+%s\n", __func__);

    // 0. Select VBUS
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) |  (3<<24), (void *)(SOC_VA_TIEOFF + 0x34));   /* Select VBUS 3.3V */
//    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) & ~(3<<24), (void *)(SOC_VA_TIEOFF + 0x34));   /* Select VBUS 5V */

    // 1. UTMI reset
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) & ~(1<<3), (void *)(SOC_VA_TIEOFF + 0x34));
    udelay(10); // 10 clock need

    // 2. AHB reset
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) & ~(1<<2), (void *)(SOC_VA_TIEOFF + 0x34));
    udelay(10); // 10 clock need

    // 3. POR of PHY
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) |  (3<<7), (void *)(SOC_VA_TIEOFF + 0x34));
    udelay(10); // 40us delay need.

    // 4. Release otg common reset
    writel(readl((void *)(SOC_VA_RSTCON + 0x04)) & ~(1<<25), (void *)(SOC_VA_RSTCON + 0x04));     // reset on
    udelay(10);
}
EXPORT_SYMBOL(otg_phy_off);

void otg_phy_suspend(void)
{
    u32 temp;

    // 0. Select VBUS
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) |  (3<<24), (void *)(SOC_VA_TIEOFF + 0x34));   /* Select VBUS 3.3V */
//    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) & ~(3<<24), (void *)(SOC_VA_TIEOFF + 0x34));   /* Select VBUS 5V */

    // 1. AHB reset
#if 0
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) & ~(1<<2), (void *)(SOC_VA_TIEOFF + 0x34));
    udelay(10); // 10 clock need
#endif

    // 2. UTMI reset
#if 0
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) & ~(1<<3), (void *)(SOC_VA_TIEOFF + 0x34));
    udelay(10); // 10 clock need
#endif

    // 3. Release otg common reset
    writel(readl((void *)(SOC_VA_RSTCON + 0x04)) & ~(1<<25), (void *)(SOC_VA_RSTCON + 0x04));     // reset on
    udelay(10);

    // 4. POR of PHY
#if 0
#if 0
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) |  (2<<7), (void *)(SOC_VA_TIEOFF + 0x34));
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) & ~(1<<7), (void *)(SOC_VA_TIEOFF + 0x34));
#else
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) & ~(3<<7), (void *)(SOC_VA_TIEOFF + 0x34));
    writel(readl((void *)(SOC_VA_TIEOFF + 0x34)) |  (2<<7), (void *)(SOC_VA_TIEOFF + 0x34));
#endif
#else

    temp    = readl((void *)(SOC_VA_TIEOFF + 0x34));
    temp   &= ~(3<<7);
    temp   |=  (2<<7);
    writel(temp, (void *)(SOC_VA_TIEOFF + 0x34));
#endif
    udelay(40); // 40us delay need.
}
EXPORT_SYMBOL(otg_phy_suspend);


#define CFG_SWITCH_USB_5V_EN        (PAD_GPIO_D + 10)
#define CFG_SWITCH_USB_HOST_DEVICE  (PAD_GPIO_D + 11)
#define CFG_OTG_MODE_HOST           1
#define CFG_OTG_MODE_DEVICE         0
#define CFG_OTG_BOOT_MODE           CFG_OTG_MODE_DEVICE

static int cur_otg_mode = CFG_OTG_BOOT_MODE;

unsigned int get_otg_mode(void)
{
    return cur_otg_mode;
}
EXPORT_SYMBOL(get_otg_mode);

void set_otg_mode(unsigned int mode, int is_force)
{
    if (mode > CFG_OTG_MODE_HOST) return;

    if ((mode == cur_otg_mode) && !is_force) return;

    cur_otg_mode = mode;

    return;
}
EXPORT_SYMBOL(set_otg_mode);
