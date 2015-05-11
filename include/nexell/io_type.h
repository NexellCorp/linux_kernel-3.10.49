#ifndef __GPIO_TYPE_H__
#define __GPIO_TYPE_H__

#define PAD_MD_POS    	0
#define PAD_MD_MASK     0xF

#define PAD_FN_POS    	4
#define PAD_FN_MASK     0xF

#define PAD_LV_POS      8
#define PAD_LV_MASK     0xF

#define PAD_PU_POS      12
#define PAD_PU_MASK     0xF

#define PAD_ST_POS      16
#define PAD_ST_MASK     0xF

#define	PAD_MODE_ALT    		((0 & PAD_MD_MASK) << PAD_MD_POS)
#define	PAD_MODE_IN     		((1 & PAD_MD_MASK) << PAD_MD_POS)
#define	PAD_MODE_OUT    		((2 & PAD_MD_MASK) << PAD_MD_POS)
#define	PAD_MODE_INT    		((3 & PAD_MD_MASK) << PAD_MD_POS)

#define	PAD_FUNC_ALT0  			((0 & PAD_FN_MASK) << PAD_FN_POS)
#define	PAD_FUNC_ALT1  			((1 & PAD_FN_MASK) << PAD_FN_POS)
#define	PAD_FUNC_ALT2  			((2 & PAD_FN_MASK) << PAD_FN_POS)
#define	PAD_FUNC_ALT3  			((3 & PAD_FN_MASK) << PAD_FN_POS)

#define PAD_LEVEL_LOW         	((0 & PAD_LV_MASK) << PAD_LV_POS)	/* if alive, async lowlevel */
#define PAD_LEVEL_HIGH        	((1 & PAD_LV_MASK) << PAD_LV_POS)   /* if alive, async highlevel */
#define PAD_LEVEL_FALLINGEDGE 	((2 & PAD_LV_MASK) << PAD_LV_POS)   /* if alive, async fallingedge */
#define PAD_LEVEL_RISINGEDGE  	((3 & PAD_LV_MASK) << PAD_LV_POS)   /* if alive, async eisingedge */
#define PAD_LEVEL_LOW_SYNC    	((4 & PAD_LV_MASK) << PAD_LV_POS)   /* if gpio , not support */
#define PAD_LEVEL_HIGH_SYNC   	((5 & PAD_LV_MASK) << PAD_LV_POS)   /* if gpio , not support */
#define PAD_LEVEL_BOTHEDGE    	((4 & PAD_LV_MASK) << PAD_LV_POS)   /* if alive, not support */
#define PAD_LEVEL_ALT         	((6 & PAD_LV_MASK) << PAD_LV_POS)   /* if pad function is alt, not set */

#define PAD_PULL_DN     		((0 & PAD_PU_MASK) << PAD_PU_POS)   /* Do not support Alive-GPIO */
#define PAD_PULL_UP     		((1 & PAD_PU_MASK) << PAD_PU_POS)
#define PAD_PULL_OFF    		((2 & PAD_PU_MASK) << PAD_PU_POS)

#define PAD_STRENGTH_0 			((0 & PAD_ST_MASK) << PAD_ST_POS)
#define PAD_STRENGTH_1 			((1 & PAD_ST_MASK) << PAD_ST_POS)
#define PAD_STRENGTH_2 			((2 & PAD_ST_MASK) << PAD_ST_POS)
#define PAD_STRENGTH_3 			((3 & PAD_ST_MASK) << PAD_ST_POS)


#define PAD_GET_GROUP(pin)      ((pin >> 0x5) & 0x07)       /* Divide 32 */
#define PAD_GET_BITNO(pin)      (pin & 0x1F)
#define PAD_GET_FUNC(pin)       ((pin >> PAD_FN_POS) & PAD_FN_MASK)
#define PAD_GET_MODE(pin)       ((pin >> PAD_MD_POS) & PAD_MD_MASK)
#define PAD_GET_LEVEL(pin)      ((pin >> PAD_LV_POS) & PAD_LV_MASK)
#define PAD_GET_PULLUP(pin)     ((pin >> PAD_PU_POS) & PAD_PU_MASK)
#define PAD_GET_STRENGTH(pin)   ((pin >> PAD_ST_POS) & PAD_ST_MASK)

#define PAD_GPIO_A      		(0 * 32)
#define PAD_GPIO_B      		(1 * 32)
#define PAD_GPIO_C      		(2 * 32)
#define PAD_GPIO_D      		(3 * 32)
#define PAD_GPIO_E      		(4 * 32)
#define PAD_GPIO_ALV    		(5 * 32)

#endif
