#ifndef __NXP_FTL_NAND_H__
#define __NXP_FTL_NAND_H__ __FILE__

/******************************************************************************
 *
 ******************************************************************************/
#define DEV_NAME_NAND "nxp-nand"



/******************************************************************************
 *
 ******************************************************************************/
struct nxp_ftl_nand {
	unsigned long nxp_ftl_start_block; /* byte address, Must Be Multiple of 8MB */

	void __iomem *io_ctrl;			// CONTROL Regs.  : NFCONTROL, NFECCTRL, ...
	void __iomem *io_intf;			// INTERFACE Regs.: NFDATA, NFCMD, NFADDR
	struct clk *clk;
	uint32_t clkhz;
};

extern struct nxp_ftl_nand nxp_nand;



#endif /* __NXP_FTL_NAND_H__ */
