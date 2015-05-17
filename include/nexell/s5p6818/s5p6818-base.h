#ifndef _S5P6818_BASE_H
#define _S5P6818_BASE_H

#define PHYS_BASE_DMA0     		(0xC0000000)
#define PHYS_BASE_DMA1     		(0xC0001000)
#define PHYS_BASE_INT     		(0xC0008000)
#define PHYS_BASE_INT_DIST		(0xC0009000)
#define PHYS_BASE_INT_CPU		(0xC000a000)
#define PHYS_BASE_CLKPWR		(0xC0010000)
#define PHYS_BASE_RTC			(0xC0010C00)
#define PHYS_BASE_ALIVE			(0xC0010800)
#define PHYS_BASE_RSTCON		(0xC0012000)
#define PHYS_BASE_TIEOFF		(0xC0011000)
#define PHYS_BASE_PDM			(0xC0014000)
#define PHYS_BASE_CRYPTO		(0xC0015000)
#define PHYS_BASE_TIMER			(0xC0017000)
#define PHYS_BASE_PWM			(0xC0018000)
#define PHYS_BASE_WDT			(0xC0019000)
#define PHYS_BASE_GPIOA			(0xC001A000)
#define PHYS_BASE_GPIOB			(0xC001B000)
#define PHYS_BASE_GPIOC			(0xC001C000)
#define PHYS_BASE_GPIOD			(0xC001D000)
#define PHYS_BASE_GPIOE			(0xC001E000)
#define PHYS_BASE_OHCI			(0xC0020000)
#define PHYS_BASE_EHCI			(0xC0030000)
#define PHYS_BASE_HSOTG			(0xC0040000)
#define PHYS_BASE_ADC			(0xC0053000)
#define PHYS_BASE_PPM			(0xC0054000)
#define PHYS_BASE_I2S0     		(0xC0055000)
#define PHYS_BASE_I2S1     		(0xC0056000)
#define PHYS_BASE_I2S2     		(0xC0057000)
#define PHYS_BASE_AC97			(0xC0058000)
#define PHYS_BASE_SPDIF_TX		(0xC0059000)
#define PHYS_BASE_SPDIF_RX		(0xC005A000)
#define PHYS_BASE_SSP0			(0xC005B000)
#define PHYS_BASE_SSP1			(0xC005C000)
#define PHYS_BASE_SSP2			(0xC005F000)
#define PHYS_BASE_MPEGTSI		(0xC005D000)
#define PHYS_BASE_GMAC			(0xC0060000)
#define PHYS_BASE_VIP0			(0xC0063000)
#define PHYS_BASE_VIP1			(0xC0064000)
#define PHYS_BASE_VIP2			(0xC0099000)
#define PHYS_BASE_DEINTERLACE	(0xC0065000)
#define PHYS_BASE_SCALER		(0xC0066000)
#define PHYS_BASE_ECID			(0xC0067000)
#define PHYS_BASE_SDMMC0		(0xC0062000)
#define PHYS_BASE_SDMMC1		(0xC0068000)
#define PHYS_BASE_SDMMC2		(0xC0069000)
#define PHYS_BASE_VR			(0xC0070000)
#define PHYS_BASE_CODA_APB0		(0xC0080000)
#define PHYS_BASE_CODA_APB1		(0xC0081000)
#define PHYS_BASE_CODA_APB2		(0xC0082000)
#define PHYS_BASE_CODA_APB3		(0xC0083000)
#define PHYS_BASE_UART0         (0xC00A1000)	// dma (O), modem(X), UART0_MODULE
#define PHYS_BASE_UART1         (0xC00A0000)	// dma (O), modem(O), pl01115_Uart_modem_MODULE
#define PHYS_BASE_UART2         (0xC00A2000)	// dma (O), modem(X), UART1_MODULE
#define PHYS_BASE_UART3         (0xC00A3000)	// dma (X), modem(X), pl01115_Uart_nodma0_MODULE
#define PHYS_BASE_UART4         (0xC006D000)	// dma (X), modem(X), pl01115_Uart_nodma1_MODULE
#define PHYS_BASE_UART5         (0xC006F000)	// dma (X), modem(X), pl01115_Uart_nodma2_MODULE
#define PHYS_BASE_I2C0          (0xC00A4000)
#define PHYS_BASE_I2C1          (0xC00A5000)
#define PHYS_BASE_I2C2          (0xC00A6000)
#define PHYS_BASE_CAN0			(0xC00CE000)
#define PHYS_BASE_CAN1			(0xC00CF000)
#define PHYS_BASE_MIPI			(0xC00D0000)
#define PHYS_BASE_DISPLAYTOP	(0xC0100000)

#define PHY_BASEADDR_CS_NAND	(0x2C000000)

#define PHYS_BASE_CLK_0			(0xC00BB000)	// TIMER_1
#define PHYS_BASE_CLK_1			(0xC00BC000)	// TIMER_2
#define PHYS_BASE_CLK_2			(0xC00BD000)	// TIMER_3
#define PHYS_BASE_CLK_3			(0xC00BE000)	// PWM_1
#define PHYS_BASE_CLK_4			(0xC00BF000)	// PWM_2
#define PHYS_BASE_CLK_5			(0xC00C0000)	// PWM_3
#define PHYS_BASE_CLK_6			(0xC00AE000)	// I2C_0
#define PHYS_BASE_CLK_7			(0xC00AF000)	// I2C_1
#define PHYS_BASE_CLK_8			(0xC00B0000)	// I2C_2
#define PHYS_BASE_CLK_9			(0xC00CA000)	// MIPI
#define PHYS_BASE_CLK_10		(0xC00C8000)	// GMAC
#define PHYS_BASE_CLK_11		(0xC00B8000)	// SPDIF_TX
#define PHYS_BASE_CLK_12		(0xC00B7000)	// MPEGTSI
#define PHYS_BASE_CLK_13		(0xC00BA000)	// PWM_0
#define PHYS_BASE_CLK_14		(0xC00B9000)	// TIMER_0
#define PHYS_BASE_CLK_15		(0xC00B2000)	// I2S_0
#define PHYS_BASE_CLK_16		(0xC00B3000)	// I2S_1
#define PHYS_BASE_CLK_17		(0xC00B4000)	// I2S_2
#define PHYS_BASE_CLK_18		(0xC00C5000)	// SDHC_0
#define PHYS_BASE_CLK_19		(0xC00CC000)	// SDHC_1
#define PHYS_BASE_CLK_20		(0xC00CD000)	// SDHC_2
#define PHYS_BASE_CLK_21		(0xC00C3000)	// VR
#define PHYS_BASE_CLK_22		(0xC00A9000)	// UART_0
#define PHYS_BASE_CLK_23		(0xC00AA000)	// UART_2
#define PHYS_BASE_CLK_24		(0xC00A8000)	// UART_1
#define PHYS_BASE_CLK_25		(0xC00AB000)	// UART_3
#define PHYS_BASE_CLK_26		(0xC006E000)	// UART_4
#define PHYS_BASE_CLK_27		(0xC00B1000)	// UART_5
#define PHYS_BASE_CLK_28		(0xC00B5000)	// DEINTERLACE
#define PHYS_BASE_CLK_29		(0xC00C4000)	// PPM
#define PHYS_BASE_CLK_30		(0xC00C1000)	// VIP_0
#define PHYS_BASE_CLK_31		(0xC00C2000)	// VIP_1
#define PHYS_BASE_CLK_32		(0xC006B000)	// USB2HOST
#define PHYS_BASE_CLK_33		(0xC00C7000)	// CODA
#define PHYS_BASE_CLK_34		(0xC00C6000)	// CRYPTO
#define PHYS_BASE_CLK_35		(0xC00B6000)	// SCALER
#define PHYS_BASE_CLK_36		(0xC00CB000)	// PDM
#define PHYS_BASE_CLK_37		(0xC00AC000)	// SPI0
#define PHYS_BASE_CLK_38		(0xC00AD000)	// SPI1
#define PHYS_BASE_CLK_39		(0xC00A7000)	// SPI2
#define PHYS_BASE_CLK_40		(0xC009A000)
#define PHYS_BASE_CLK_DREX		(0xC00E0000)

/* IP Reset ID */
#define	RESET_ID_AC97				0
#define	RESET_ID_CPU1				1
#define	RESET_ID_CPU2				2
#define	RESET_ID_CPU3				3
#define	RESET_ID_WD1				4
#define	RESET_ID_WD2				5
#define	RESET_ID_WD3				6
#define	RESET_ID_CRYPTO				7
#define	RESET_ID_DEINTERLACE		8
#define	RESET_ID_DISP_TOP			9
#define RESET_ID_DISPLAY			10	/* DualDisplay -: MLC0/1, DPC0/1 */
#define RESET_ID_RESCONV			11
#define RESET_ID_LCDIF				12
#define RESET_ID_HDMI				13
#define RESET_ID_HDMI_VIDEO			14
#define RESET_ID_HDMI_SPDIF			15
#define RESET_ID_HDMI_TMDS			16
#define RESET_ID_HDMI_PHY			17
#define RESET_ID_LVDS				18
#define RESET_ID_ECID				19
#define RESET_ID_I2C0				20
#define RESET_ID_I2C1				21
#define RESET_ID_I2C2				22
#define RESET_ID_I2S0				23
#define RESET_ID_I2S1				24
#define RESET_ID_I2S2				25
#define RESET_ID_DREX_C				26
#define RESET_ID_DREX_A				27
#define RESET_ID_DREX				28
#define RESET_ID_MIPI				29
#define RESET_ID_MIPI_DSI			30
#define RESET_ID_MIPI_CSI			31
#define RESET_ID_MIPI_PHY_S			32
#define RESET_ID_MIPI_PHY_M			33
#define	RESET_ID_MPEGTSI			34
#define RESET_ID_PDM				35
#define RESET_ID_TIMER				36
#define RESET_ID_PWM				37
#define RESET_ID_SCALER				38
#define RESET_ID_SDMMC0				39
#define RESET_ID_SDMMC1				40
#define RESET_ID_SDMMC2				41
#define RESET_ID_SPDIFRX			42
#define RESET_ID_SPDIFTX			43
#define	RESET_ID_SSP0_P				44
#define RESET_ID_SSP0				45
#define RESET_ID_SSP1_P				46
#define RESET_ID_SSP1				47
#define RESET_ID_SSP2_P				48
#define RESET_ID_SSP2				49
#define RESET_ID_UART0				50	/* UART1 */
#define RESET_ID_UART1				51	/* pl01115_Uart_modem	*/
#define RESET_ID_UART2				52	/* UART1 */
#define RESET_ID_UART3				53	/* pl01115_Uart_nodma0 */
#define RESET_ID_UART4				54	/* pl01115_Uart_nodma1 */
#define RESET_ID_UART5				55	/* pl01115_Uart_nodma2 */
#define RESET_ID_USB20HOST			56
#define RESET_ID_USB20OTG			57
#define RESET_ID_WDT				58
#define RESET_ID_WDT_POR			59
#define RESET_ID_ADC				60
#define RESET_ID_CODA_A				61
#define RESET_ID_CODA_P				62
#define RESET_ID_CODA_C				63
#define RESET_ID_DWC_GMAC			64
#define RESET_ID_VR					65
#define RESET_ID_PPM				66
#define RESET_ID_VIP1				67
#define RESET_ID_VIP0               68

/*
 * clock
 */
#define	CLK_CPU_PLL0		"sys-pll0"
#define	CLK_CPU_PLL1		"sys-pll1"
#define	CLK_CPU_PLL2		"sys-pll2"
#define	CLK_CPU_PLL3		"sys-pll3"
#define	CLK_CPU_FCLK		"sys-cfclk"
#define	CLK_CPU_HCLK		"sys-chclk"
#define	CLK_MEM_FCLK		"sys-mfclk"
#define	CLK_MEM_DCLK		"sys-mdclk"
#define	CLK_MEM_BCLK		"sys-mbclk"
#define	CLK_MEM_PCLK		"sys-mpclk"
#define	CLK_BUS_BCLK		"sys-bbclk"
#define	CLK_BUS_PCLK		"sys-bpclk"
#define	CLK_VPU_BCLK		"sys-vpubclk"
#define	CLK_VPU_PCLK		"sys-vpupclk"
#define	CLK_DIS_BCLK		"sys-disbclk"
#define	CLK_DIS_PCLK		"sys-disspclk"
#define	CLK_CCI_BCLK		"sys-ccibclk"
#define	CLK_CCI_PCLK		"sys-ccipclk"
#define	CLK_G3D_BCLK		"sys-g3dbclk"

#define CLK_ID_TIMER_1			0
#define CLK_ID_TIMER_2			1
#define CLK_ID_TIMER_3			2
#define CLK_ID_PWM_1			3
#define CLK_ID_PWM_2			4
#define CLK_ID_PWM_3			5
#define CLK_ID_I2C_0			6
#define CLK_ID_I2C_1			7
#define CLK_ID_I2C_2			8
#define CLK_ID_MIPI				9
#define CLK_ID_GMAC				10	/* External Clock 1 */
#define CLK_ID_SPDIF_TX			11
#define CLK_ID_MPEGTSI			12
#define CLK_ID_PWM_0			13
#define CLK_ID_TIMER_0			14
#define CLK_ID_I2S_0			15	/* External Clock 1 */
#define CLK_ID_I2S_1			16	/* External Clock 1 */
#define CLK_ID_I2S_2			17	/* External Clock 1 */
#define CLK_ID_SDHC_0			18
#define CLK_ID_SDHC_1			19
#define CLK_ID_SDHC_2			20
#define CLK_ID_VR				21
#define CLK_ID_UART_0			22	/* UART0_MODULE */
#define CLK_ID_UART_2			23	/* UART1_MODULE */
#define CLK_ID_UART_1			24	/* pl01115_Uart_modem_MODULE  */
#define CLK_ID_UART_3			25	/* pl01115_Uart_nodma0_MODULE */
#define CLK_ID_UART_4			26	/* pl01115_Uart_nodma1_MODULE */
#define CLK_ID_UART_5			27	/* pl01115_Uart_nodma2_MODULE */
#define CLK_ID_DIT				28
#define CLK_ID_PPM				29
#define CLK_ID_VIP_0			30	/* External Clock 1 */
#define CLK_ID_VIP_1			31	/* External Clock 1, 2 */
#define CLK_ID_USB2HOST			32	/* External Clock 2 */
#define CLK_ID_CODA				33
#define CLK_ID_CRYPTO			34
#define CLK_ID_SCALER			35
#define CLK_ID_PDM				36
#define CLK_ID_SPI_0			37
#define CLK_ID_SPI_1			38
#define CLK_ID_SPI_2			39
#define CLK_ID_MAX				39
#define CLK_ID_USBOTG			40	/* Shared with USB2HOST */

#define	I_PLL0_BIT			(0)
#define	I_PLL1_BIT			(1)
#define	I_PLL2_BIT			(2)
#define	I_PLL3_BIT			(3)
#define	I_EXT1_BIT			(4)
#define	I_EXT2_BIT			(5)
#define	I_CLKn_BIT			(7)

#define	I_PLL0 				(1 << I_PLL0_BIT)
#define	I_PLL1 				(1 << I_PLL1_BIT)
#define	I_PLL2 				(1 << I_PLL2_BIT)
#define	I_PLL3 				(1 << I_PLL3_BIT)
#define	I_EXTCLK1 			(1 << I_EXT1_BIT)
#define	I_EXTCLK2 			(1 << I_EXT2_BIT)

#define	I_PLL_0_1			(I_PLL0    | I_PLL1)
#define	I_PLL_0_2			(I_PLL_0_1 | I_PLL2)
#define	I_PLL_0_3			(I_PLL_0_2 | I_PLL3)
#define	I_CLKnOUT			(0)

#define	I_PCLK				(1<< 8)
#define	I_BCLK				(1<< 9)
#define	I_GATE_PCLK			(1<<12)
#define	I_GATE_BCLK			(1<<13)
#define	I_PCLK_MASK			(I_GATE_PCLK | I_PCLK)
#define	I_BCLK_MASK			(I_GATE_BCLK | I_BCLK)

#define	CLK_INPUT_TIMER		(I_PLL_0_2)
#define	CLK_INPUT_UART		(I_PLL_0_2)
#define	CLK_INPUT_PWM		(I_PLL_0_2)
#define	CLK_INPUT_I2C		(I_GATE_PCLK)
#define	CLK_INPUT_SDHC		(I_PLL_0_2|I_GATE_PCLK)
#define	CLK_INPUT_I2S		(I_PLL_0_3|I_EXTCLK1)
#define	CLK_INPUT_I2S_IN1	(I_CLKnOUT)
#define	CLK_INPUT_SPI		(I_PLL_0_2)
#define	CLK_INPUT_VIP0		(I_PLL_0_3|I_EXTCLK1|I_GATE_BCLK)
#define	CLK_INPUT_VIP1		(I_PLL_0_3|I_EXTCLK1|I_EXTCLK2|I_GATE_BCLK)
#define	CLK_INPUT_MIPI		(I_PLL_0_2)
#define	CLK_INPUT_GMAC		(I_PLL_0_3|I_EXTCLK1)
#define	CLK_INPUT_GMAC_IN1	(I_CLKnOUT)
#define	CLK_INPUT_SPDIFTX	(I_PLL_0_2)
#define	CLK_INPUT_MPEGTS	(I_GATE_BCLK)
#define	CLK_INPUT_VR		(I_GATE_BCLK)
#define	CLK_INPUT_DIT		(I_GATE_BCLK)
#define	CLK_INPUT_PPM		(I_PLL_0_2)
#define	CLK_INPUT_EHCI		(I_PLL_0_3)
#define	CLK_INPUT_EHCI_IN1	(I_PLL_0_3|I_EXTCLK1)
#define	CLK_INPUT_VPU		(I_GATE_PCLK|I_GATE_BCLK)
#define	CLK_INPUT_CRYPTO	(I_GATE_PCLK)
#define	CLK_INPUT_SCALER	(I_GATE_BCLK)
#define	CLK_INPUT_OTG		(I_PLL_0_3)
#define	CLK_INPUT_OTG_IN1	(I_PLL_0_3|I_EXTCLK1)
#define	CLK_INPUT_PDM		(I_GATE_PCLK)

/*
 * DMA
 */
#define	PL08X_DMA_ID_UART1_TX			0	// pl01115_Uart_modem_MODULE
#define	PL08X_DMA_ID_UART1_RX			1	// pl01115_Uart_modem_MODULE
#define	PL08X_DMA_ID_UART0_TX			2	// UART0_MODULE
#define	PL08X_DMA_ID_UART0_RX			3	// UART0_MODULE
#define	PL08X_DMA_ID_UART2_TX			4	// UART1_MODULE
#define	PL08X_DMA_ID_UART2_RX			5	// UART1_MODULE
#define	PL08X_DMA_ID_SSP0_TX			6
#define	PL08X_DMA_ID_SSP0_RX			7
#define	PL08X_DMA_ID_SSP1_TX			8
#define	PL08X_DMA_ID_SSP1_RX			9
#define	PL08X_DMA_ID_SSP2_TX			10
#define	PL08X_DMA_ID_SSP2_RX			11
#define	PL08X_DMA_ID_I2S0_TX			12
#define	PL08X_DMA_ID_I2S0_RX			13
#define	PL08X_DMA_ID_I2S1_TX			14
#define	PL08X_DMA_ID_I2S1_RX			15
#define	PL08X_DMA_ID_I2S2_TX			16
#define	PL08X_DMA_ID_I2S2_RX			17
#define	PL08X_DMA_ID_AC97_PCMOUT		18
#define	PL08X_DMA_ID_AC97_PCMIN			19
#define	PL08X_DMA_ID_AC97_MICIN			20
#define	PL08X_DMA_ID_SPDIFRX			21
#define	PL08X_DMA_ID_SPDIFTX			22
#define	PL08X_DMA_ID_MPEGTSI0			23
#define	PL08X_DMA_ID_MPEGTSI1			24
#define	PL08X_DMA_ID_MPEGTSI2			25
#define	PL08X_DMA_ID_MPEGTSI3			26
#define	PL08X_DMA_ID_CRYPTO_BR			27
#define	PL08X_DMA_ID_CRYPTO_BW			28
#define	PL08X_DMA_ID_CRYPTO_HR			29
#define	PL08X_DMA_ID_PDM				30

#define	PL08X_DMA_NAME_UART1_TX			"uart1_tx"			// ID: 0, pl01115_Uart_modem_MODULE
#define	PL08X_DMA_NAME_UART1_RX			"uart1_rx"     		// ID: 1, pl01115_Uart_modem_MODULE
#define	PL08X_DMA_NAME_UART0_TX			"uart0_tx"          // ID: 2, UART0_MODULE
#define	PL08X_DMA_NAME_UART0_RX			"uart0_rx"          // ID: 3, UART0_MODULE
#define	PL08X_DMA_NAME_UART2_TX			"uart2_tx"          // ID: 4, UART1_MODULE
#define	PL08X_DMA_NAME_UART2_RX			"uart2_rx"          // ID: 5, UART1_MODULE
#define	PL08X_DMA_NAME_SSP0_TX			"ssp0_tx"           // ID: 6
#define	PL08X_DMA_NAME_SSP0_RX			"ssp0_rx"           // ID: 7
#define	PL08X_DMA_NAME_SSP1_TX			"ssp1_tx"           // ID: 8
#define	PL08X_DMA_NAME_SSP1_RX			"ssp1_rx"           // ID: 9
#define	PL08X_DMA_NAME_SSP2_TX			"ssp2_tx"           // ID: 10
#define	PL08X_DMA_NAME_SSP2_RX			"ssp2_rx"           // ID: 11
#define	PL08X_DMA_NAME_I2S0_TX			"i2s0_tx"           // ID: 12
#define	PL08X_DMA_NAME_I2S0_RX			"i2s0_rx"           // ID: 13
#define	PL08X_DMA_NAME_I2S1_TX			"i2s1_tx"           // ID: 14
#define	PL08X_DMA_NAME_I2S1_RX			"i2s1_rx"           // ID: 15
#define	PL08X_DMA_NAME_I2S2_TX			"i2s2_tx"			// ID: 16
#define	PL08X_DMA_NAME_I2S2_RX			"i2s2_rx"           // ID: 17
#define	PL08X_DMA_NAME_AC97_PCMOUT		"ac97_pcmout"       // ID: 18
#define	PL08X_DMA_NAME_AC97_PCMIN		"ac97_pcmin"        // ID: 19
#define	PL08X_DMA_NAME_AC97_MICIN		"ac97_micin"        // ID: 20
#define	PL08X_DMA_NAME_SPDIFRX			"spdif_rx"          // ID: 21
#define	PL08X_DMA_NAME_SPDIFTX			"spdif_tx"          // ID: 22
#define	PL08X_DMA_NAME_MPEGTSI0			"mpegtsi0"          // ID: 23
#define	PL08X_DMA_NAME_MPEGTSI1			"mpegtsi1"          // ID: 24
#define	PL08X_DMA_NAME_MPEGTSI2			"mpegtsi2"          // ID: 25
#define	PL08X_DMA_NAME_MPEGTSI3			"mpegtsi3"          // ID: 26
#define	PL08X_DMA_NAME_CRYPTO_BR		"crypto_br"         // ID: 27
#define	PL08X_DMA_NAME_CRYPTO_BW		"crypto_bw"         // ID: 28
#define	PL08X_DMA_NAME_CRYPTO_HR		"crypto_hr"         // ID: 29
#define	PL08X_DMA_NAME_PDM				"pdm"               // ID: 30

/*
 * Refer to include/linux/amba/pl080.h
 */
#define	PL08X_AHB1	(1 << 0)
#define	PL08X_AHB2	(1 << 1)

#define PL080_CONTROL_TC_IRQ_EN			(1 << 31)
#define PL080_CONTROL_PROT_MASK			(0x7 << 28)
#define PL080_CONTROL_PROT_SHIFT		(28)
#define PL080_CONTROL_PROT_CACHE		(1 << 30)
#define PL080_CONTROL_PROT_BUFF			(1 << 29)
#define PL080_CONTROL_PROT_SYS			(1 << 28)
#define PL080_CONTROL_DST_INCR			(1 << 27)
#define PL080_CONTROL_SRC_INCR			(1 << 26)
#define PL080_CONTROL_DST_AHB2			(1 << 25)
#define PL080_CONTROL_SRC_AHB2			(1 << 24)
#define PL080_CONTROL_DWIDTH_MASK		(0x7 << 21)
#define PL080_CONTROL_DWIDTH_SHIFT		(21)
#define PL080_CONTROL_SWIDTH_MASK		(0x7 << 18)
#define PL080_CONTROL_SWIDTH_SHIFT		(18)
#define PL080_CONTROL_DB_SIZE_MASK		(0x7 << 15)
#define PL080_CONTROL_DB_SIZE_SHIFT		(15)
#define PL080_CONTROL_SB_SIZE_MASK		(0x7 << 12)
#define PL080_CONTROL_SB_SIZE_SHIFT		(12)
#define PL080_CONTROL_TRANSFER_SIZE_MASK	(0xfff << 0)
#define PL080_CONTROL_TRANSFER_SIZE_SHIFT	(0)

#define PL080_BSIZE_1				(0x0)
#define PL080_BSIZE_4				(0x1)
#define PL080_BSIZE_8				(0x2)
#define PL080_BSIZE_16				(0x3)
#define PL080_BSIZE_32				(0x4)
#define PL080_BSIZE_64				(0x5)
#define PL080_BSIZE_128				(0x6)
#define PL080_BSIZE_256				(0x7)

#define PL080_WIDTH_8BIT			(0x0)
#define PL080_WIDTH_16BIT			(0x1)
#define PL080_WIDTH_32BIT			(0x2)

#define PRIMECELL_MEMORU_CCTL   (PL080_BSIZE_256 << PL080_CONTROL_SB_SIZE_SHIFT |   \
            PL080_BSIZE_256 << PL080_CONTROL_DB_SIZE_SHIFT |    \
            PL080_WIDTH_32BIT << PL080_CONTROL_SWIDTH_SHIFT |   \
            PL080_WIDTH_32BIT << PL080_CONTROL_DWIDTH_SHIFT |   \
            PL080_CONTROL_PROT_BUFF |               \
            PL080_CONTROL_PROT_CACHE |              \
            PL080_CONTROL_PROT_SYS)

/* redefine */
#define TIEOFF_MMC_8BIT 								((1<<16) | 5  )
#define TIEOFF_AXISRAM0_i_TIE_ra2w_EMAA 				((3<<16) | 47 )
#define TIEOFF_AXISRAM0_i_TIE_ra2w_EMAB 				((3<<16) | 50 )
#define TIEOFF_AXISRAM0_i_TIE_ra2w_EMAWA 				((2<<16) | 53 )
#define TIEOFF_AXISRAM0_i_TIE_ra2w_EMAWB 				((2<<16) | 55 )
#define TIEOFF_AXISRAM0_i_nPowerDown 					((1<<16) | 57 )
#define TIEOFF_AXISRAM0_i_nSleep 						((1<<16) | 58 )
#define TIEOFF_CAN0_i_TIE_rf1_EMA 						((3<<16) | 59 )
#define TIEOFF_CAN0_i_TIE_rf1_EMAW 						((2<<16) | 62 )
#define TIEOFF_CAN0_i_nPowerDown 						((1<<16) | 64 )
#define TIEOFF_CAN0_i_nSleep 							((1<<16) | 65 )
#define TIEOFF_CAN1_i_TIE_rf1_EMA 						((3<<16) | 66 )
#define TIEOFF_CAN1_i_TIE_rf1_EMAW 						((2<<16) | 69 )
#define TIEOFF_CAN1_i_nPowerDown 						((1<<16) | 71 )
#define TIEOFF_CAN1_i_nSleep 							((1<<16) | 72 )
#define TIEOFF_DEINTERLACE0_i_NX_RF1_EMA 				((3<<16) | 73 )
#define TIEOFF_DEINTERLACE0_i_NX_RF1_EMAW 				((2<<16) | 76 )
#define TIEOFF_DEINTERLACE0_i_NX_RF2_EMAA 				((3<<16) | 78 )
#define TIEOFF_DEINTERLACE0_i_NX_RF2_EMAB 				((3<<16) | 81 )
#define TIEOFF_DEINTERLACE0_i_NX_RF2W_EMAA 				((3<<16) | 84 )
#define TIEOFF_DEINTERLACE0_i_NX_RF2W_EMAB 				((3<<16) | 87 )
#define TIEOFF_DISPLAYTOP0_i_ResConv_nPowerDown 		((1<<16) | 90 )
#define TIEOFF_DISPLAYTOP0_i_ResConv_nSleep 			((1<<16) | 91 )
#define TIEOFF_DISPLAYTOP0_i_HDMI_nPowerDown 			((2<<16) | 92 )
#define TIEOFF_DISPLAYTOP0_i_HDMI_nSleep 				((2<<16) | 94 )
#define TIEOFF_DISPLAYTOP0_i_HDMI_PHY_REFCLK_SEL		((1<<16) | 96 )
#define TIEOFF_DISPLAYTOP0_i_TIEOFF_SPSRAM_EMA 			((3<<16) | 97 )
#define TIEOFF_DISPLAYTOP0_i_TIEOFF_SPSRAM_EMAW 		((2<<16) | 100)
#define TIEOFF_DISPLAYTOP0_i_TIEOFF_DPSRAM_1R1W_EMAA 	((3<<16) | 102)
#define TIEOFF_DISPLAYTOP0_i_TIEOFF_DPSRAM_1R1W_EMAB 	((3<<16) | 105)
#define TIEOFF_DISPLAYTOP0_i_TIEOFF_DPSRAM_EMAA 		((3<<16) | 108)
#define TIEOFF_DISPLAYTOP0_i_TIEOFF_DPSRAM_EMAB 		((3<<16) | 111)
#define TIEOFF_DISPLAYTOP0_i_TIEOFF_DPSRAM_EMAWA 		((2<<16) | 114)
#define TIEOFF_DISPLAYTOP0_i_TIEOFF_DPSRAM_EMAWB 		((2<<16) | 116)
#define TIEOFF_MCUSTOP0_i_vrom_EMA 						((3<<16) | 118)

#define TIEOFF_MIPI0_NX_DPSRAM_1R1W_EMAA 				(3<<16) | 129)
#define TIEOFF_MIPI0_NX_DPSRAM_1R1W_EMAB 				(3<<16) | 132)
#define TIEOFF_MIPI0_i_NX_NPOWERDOWN 					(4<<16) | 135)
#define TIEOFF_MIPI0_i_NX_NSLEEP 						(4<<16) | 139)

#define TIEOFF_UART0_USESMC     						((1<<16) | 148)
#define TIEOFF_UART0_SMCTXENB   						((1<<16) | 149)
#define TIEOFF_UART0_SMCRXENB   						((1<<16) | 150)
#define TIEOFF_UART1_USESMC     						((1<<16) | 151)
#define TIEOFF_UART1_SMCTXENB   						((1<<16) | 152)
#define TIEOFF_UART1_SMCRXENB   						((1<<16) | 153)
#define TIEOFF_UART2_USESMC     						((1<<16) | 154)
#define TIEOFF_UART2_SMCTXENB   						((1<<16) | 155)
#define TIEOFF_UART2_SMCRXENB   						((1<<16) | 156)
#define TIEOFF_UART3_USESMC     						((1<<16) | 157)
#define TIEOFF_UART3_SMCTXENB   						((1<<16) | 158)
#define TIEOFF_UART3_SMCRXENB   						((1<<16) | 159)
#define TIEOFF_UART4_USESMC     						((1<<16) | 160)
#define TIEOFF_UART4_SMCTXENB   						((1<<16) | 161)
#define TIEOFF_UART4_SMCRXENB   						((1<<16) | 162)
#define TIEOFF_UART5_USESMC     						((1<<16) | 163)
#define TIEOFF_UART5_SMCTXENB   						((1<<16) | 164)
#define TIEOFF_UART5_SMCRXENB   						((1<<16) | 165)

#define TIEOFF_DWC_GMAC0_sbd_flowctrl_i 				((1<<16) | 694)
#define TIEOFF_DWC_GMAC0_phy_intf_sel_i 				((3<<16) | 695)
#define TIEOFF_DWC_GMAC0_i_NX_RF2_EMAA 					((3<<16) | 698)
#define TIEOFF_DWC_GMAC0_i_NX_RF2_EMAB 					((3<<16) | 701)

#endif
