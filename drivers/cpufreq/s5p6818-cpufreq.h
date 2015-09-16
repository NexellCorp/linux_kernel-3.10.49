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
#ifndef __S5P6818_ASV_H__
#define __S5P6818_ASV_H__

/*
 *	=============================================================================
 * 	|	ASV Group	|	0:ASV1	|	1:ASV2	|	2:ASV3	|	3:ASV4	|	4:ASV5	|
 *	-----------------------------------------------------------------------------
 * 	|	ARM_IDS		|	<= 6mA	|	<= 15mA	|	<= 38mA	|	<= 78mA	|	> 78mA	|
 *	-----------------------------------------------------------------------------
 * 	|	ARM_RO		|	<= 90	|	<= 130	|	<= 170	|	<= 200 	|	200 >	|
 *	=============================================================================
 * 	|	EMA_CPU		|	EMA:001	|	EMA:001	|	EMA:001	|	EMA:001	|	EMA:001	|
 *	=============================================================================
 * 	|  0: 1600 MHZ	|	1,360 mV|	1,350 mV|	1,270 mV|	1,240 mV|	1,225 mV|
 *	-----------------------------------------------------------------------------
 * 	|  1: 1500 MHZ	|	1,350 mV|	1,280 mV|	1,240 mV|	1,210 mV|	1,175 mV|
 *	-----------------------------------------------------------------------------
 * 	|  2: 1400 MHZ	|	1,325 mV|	1,275 mV|	1,225 mV|	1,175 mV|	1,125 mV|
 *	-----------------------------------------------------------------------------
 * 	|  3: 1300 MHZ	|	1,275 mV|	1,225 mV|	1,175 mV|	1,125 mV|	1,075 mV|
 *	-----------------------------------------------------------------------------
 * 	|  4: 1200 MHZ	|	1,225 mV|	1,175 mV|	1,125 mV|	1,075 mV|	1,025 mV|
 *	-----------------------------------------------------------------------------
 * 	|  5: 1100 MHZ	|	1,175 mV|	1,125 mV|	1,075 mV|	1,050 mV|	1,000 mV|
 *	-----------------------------------------------------------------------------
 * 	|  6: 1000 MHZ	|	1,150 mV|	1,100 mV|	1,050 mV|	1,025 mV|	1,000 mV|
 *	-----------------------------------------------------------------------------
 * 	|  7: 900 MHZ	|	1,125 mV|	1,075 mV|	1,025 mV|	1,000 mV|	1,000 mV|
 *	-----------------------------------------------------------------------------
 * 	|  8: 800 MHZ	|	1,100 mV|	1,050 mV|	1,000 mV|	1,000 mV|	1,000 mV|
 *	-----------------------------------------------------------------------------
 * 	|  9: 700 MHZ	|	1,075 mV|	1,025 mV|	1,000 mV|	1,000 mV|	1,000 mV|
 *	-----------------------------------------------------------------------------
 * 	| 10: 600 MHZ	|	1,050 mV|	1,000 mV|	1,000 mV|	1,000 mV|	1,000 mV|
 *	-----------------------------------------------------------------------------
 * 	| 11: 500 MHZ	|	1,025 mV|	1,000 mV|	1,000 mV|	1,000 mV|	1,000 mV|
 *	-----------------------------------------------------------------------------
 * 	| 12: 400 MHZ	|	1,000 mV|	1,000 mV|	1,000 mV|	1,000 mV|	1,000 mV|
 *	=============================================================================
 */
#define	VOLTAGE_STEP_UV		(1)
#define	ASV_DEFAULT_LEVEL	(0)

#define	FREQ_MAX_FREQ_KHZ	(1400*1000)
#define	FREQ_ARRAY_SIZE		(13)
#define	UV(v)				(v*1000)

struct asv_tb_info {
	int ids;
	int ro;
	long Mhz[FREQ_ARRAY_SIZE];
	long uV [FREQ_ARRAY_SIZE];
};

#define	ASB_FREQ_MHZ {	\
	[ 0] = 1600,	\
	[ 1] = 1500,	\
	[ 2] = 1400,	\
	[ 3] = 1300,	\
	[ 4] = 1200,	\
	[ 5] = 1100,	\
	[ 6] = 1000,	\
	[ 7] =  900,	\
	[ 8] =  800,	\
	[ 9] =  700,	\
	[10] =  600,	\
	[11] =  500,	\
	[12] =  400,	\
	}

static struct asv_tb_info asv_tables[] = {
	[0] = {	.ids = 6, .ro = 90,
			.Mhz = ASB_FREQ_MHZ,
			.uV  = { UV(1360), UV(1350),	/* OVER FREQ */
					 UV(1325), UV(1275), UV(1225), UV(1175), UV(1150), UV(1125),
					 UV(1100), UV(1075), UV(1050), UV(1025), UV(1000) },
	},
	[1] = {	.ids = 15, .ro = 130,
			.Mhz = ASB_FREQ_MHZ,
			.uV  = { UV(1350), UV(1280),	/* OVER FREQ */
				     UV(1275), UV(1225), UV(1175), UV(1125), UV(1100), UV(1075),
					 UV(1050), UV(1025), UV(1000), UV(1000), UV(1000) },
	},
	[2] = {	.ids = 38, .ro = 170,
			.Mhz = ASB_FREQ_MHZ,
			.uV  = { UV(1270), UV(1240),	/* OVER FREQ */
					 UV(1225), UV(1175), UV(1125), UV(1075), UV(1050), UV(1025),
					 UV(1000), UV(1000), UV(1000), UV(1000), UV(1000) },
	},
	[3] = {	.ids = 78, .ro = 200,
			.Mhz = ASB_FREQ_MHZ,
			.uV  = { UV(1240), UV(1210),	/* OVER FREQ */
					 UV(1175), UV(1125), UV(1075), UV(1050), UV(1025), UV(1000),
					 UV(1000), UV(1000), UV(1000), UV(1000), UV(1000) },
	},
	[4] = {	.ids = 78, .ro = 200,
			.Mhz = ASB_FREQ_MHZ,
			.uV  = { UV(1225), UV(1175),	/* OVER FREQ */
					 UV(1125), UV(1075), UV(1025), UV(1000), UV(1000), UV(1000),
					 UV(1000), UV(1000), UV(1000), UV(1000), UV(1000) },
	},
};
#define	ASV_ARRAY_SIZE	ARRAY_SIZE(asv_tables)

struct asv_param {
	int level;
	int ids, ro;
	int flag, group, shift;
};

static struct asv_tb_info *pAsv_Table = NULL;
static struct asv_param	Asv_Param = { 0, };

extern int nxp_cpu_id_ecid(u32 ecid[4]);

static inline unsigned int MtoL(unsigned int data, int bits)
{
	unsigned int result = 0;
	unsigned int mask = 1;
	int i = 0;
	for (i = 0; i<bits ; i++) {
		if (data&(1<<i))
			result |= mask<<(bits-i-1);
	}
	return result;
}

static int s5p4418_asv_setup_table(unsigned long (*freq_tables)[2])
{
	unsigned int ecid[4] = { 0, };
	int i, ids = 0, ro = 0;
	int idslv, rolv, asvlv;

	nxp_cpu_id_ecid(ecid);

	/* Use Fusing Flags */
	if ((ecid[2] & (1<<0))) {
		int gs = MtoL((ecid[2]>>1) & 0x07, 3);
		int ag = MtoL((ecid[2]>>4) & 0x0F, 4);

		Asv_Param.level = (ag - gs);
		if (0 > Asv_Param.level)
		    Asv_Param.level = 0;

		Asv_Param.flag = 1;
		Asv_Param.group = ag;
		Asv_Param.shift = gs;
		pAsv_Table = &asv_tables[Asv_Param.level];
		printk("DVFS: ASV[%d] IDS(%dmA) Ro(%d), Fusing Shift(%d), Group(%d)\n",
			Asv_Param.level+1, pAsv_Table->ids, pAsv_Table->ro, gs, ag);
		goto asv_done;
	}

	/* Use IDS/Ro */
	ids = MtoL((ecid[1]>>16) & 0xFF, 8);
	ro  = MtoL((ecid[1]>>24) & 0xFF, 8);

	/* find IDS Level */
	for (i=0; (ASV_ARRAY_SIZE-1) > i; i++) {
		pAsv_Table = &asv_tables[i];
		if (pAsv_Table->ids >= ids)
			break;
	}
	idslv = ASV_ARRAY_SIZE != i ? i: (ASV_ARRAY_SIZE-1);

	/* find RO Level */
	for (i=0; (ASV_ARRAY_SIZE-1) > i; i++) {
		pAsv_Table = &asv_tables[i];
		if (pAsv_Table->ro >= ro)
			break;
	}
	rolv = ASV_ARRAY_SIZE != i ? i: (ASV_ARRAY_SIZE-1);

	/* find Lowest ASV Level */
	asvlv = idslv > rolv ? rolv: idslv;

	pAsv_Table = &asv_tables[asvlv];
	Asv_Param.level = asvlv;
	Asv_Param.ids = ids;
	Asv_Param.ro  = ro;
	printk("DVFS: ASV[%d] IDS %dmA, Ro %3d -> Table [IDS %dmA, Ro %3d]\n",
			Asv_Param.level+1, ids, ro, pAsv_Table->ids, pAsv_Table->ro);

asv_done:
	for (i=0; FREQ_ARRAY_SIZE > i; i++) {
		freq_tables[i][0] = pAsv_Table->Mhz[i] * 1000;	/* frequency */
		freq_tables[i][1] = pAsv_Table->uV [i];			/* voltage */
	}

	return FREQ_ARRAY_SIZE;
}

static long s5p4418_asv_get_voltage(long freqkhz)
{
	long uV = 0;
	int i = 0;

	if (NULL == pAsv_Table)
		return -EINVAL;

	for (i = 0; FREQ_ARRAY_SIZE > i; i++) {
		if (freqkhz == (pAsv_Table->Mhz[i]*1000)) {
			uV = pAsv_Table->uV[i];
			break;
		}
	}

	if (0 == uV) {
		printk("FAIL: %ldkhz is not exist on the ASV TABLEs !!!\n", freqkhz);
		return -EINVAL;
	}

	return uV;
}

#if defined (CONFIG_REGULATOR_MP8845C)
#define	_V(v)	(v*100)

static long find_uV(long uV)
{
	static const int vout_uV_list[] = {
/*  0 */	_V( 6000), _V( 6067), _V( 6134), _V( 6201), _V( 6268), _V( 6335), _V( 6401), _V( 6468), _V( 6535), _V( 6602),
/* 10 */	_V( 6669), _V( 6736), _V( 6803), _V( 6870), _V( 6937), _V( 7004), _V( 7070), _V( 7137), _V( 7204), _V( 7271),
/* 20 */	_V( 7338), _V( 7405), _V( 7472), _V( 7539), _V( 7606), _V( 7673), _V( 7739), _V( 7806), _V( 7873), _V( 7940),
/* 30 */	_V( 8007), _V( 8074), _V( 8141), _V( 8208), _V( 8275), _V( 8342), _V( 8408), _V( 8475), _V( 8542), _V( 8609),
/* 40 */	_V( 8676), _V( 8743), _V( 8810), _V( 8877), _V( 8944), _V( 9011), _V( 9077), _V( 9144), _V( 9211), _V( 9278),
/* 50 */	_V( 9345), _V( 9412), _V( 9479), _V( 9546), _V( 9613), _V( 9680), _V( 9746), _V( 9813), _V( 9880), _V( 9947),
/* 60 */	_V(10014), _V(10081), _V(10148), _V(10215), _V(10282), _V(10349), _V(10415), _V(10482), _V(10549), _V(10616),
/* 70 */	_V(10683), _V(10750), _V(10817), _V(10884), _V(10951), _V(11018), _V(11084), _V(11151), _V(11218), _V(11285),
/* 80 */	_V(11352), _V(11419), _V(11486), _V(11553), _V(11620), _V(11687), _V(11753), _V(11820), _V(11887), _V(11954),
/* 90 */	_V(12021), _V(12088), _V(12155), _V(12222), _V(12289), _V(12356), _V(12422), _V(12489), _V(12556), _V(12623),
/*100 */	_V(12690), _V(12757), _V(12824), _V(12891), _V(12958), _V(13025), _V(13091), _V(13158), _V(13225), _V(13292),
/*110 */	_V(13359), _V(13426), _V(13493), _V(13560), _V(13627), _V(13694), _V(13760), _V(13827), _V(13894), _V(13961),
/*120 */	_V(14028), _V(14095), _V(14162), _V(14229), _V(14296), _V(14363), _V(14429), _V(14496),
		};

	int size = ARRAY_SIZE(vout_uV_list);
	int ret = 0;

	/* find upper vol */
  	for (ret = 0; ret < size; ret++) {
    	if (vout_uV_list[ret] >= uV)
			break;
  	}

	if (ret == size)
		ret = size - 1;

  	return vout_uV_list[ret];
}
#endif

static int s5p4418_asv_modify_vol_table(unsigned long (*freq_tables)[2], int table_size,
				long value, bool down, bool percent)
{
	long uV, dv, new;
	int i = 0, n = 0;
	int al = 0;

	if (NULL == freq_tables ||
		NULL == pAsv_Table || (0 > value))
		return -EINVAL;

	/* initialzie */
	for (i = 0; table_size > i; i++) {
		for (n = 0; FREQ_ARRAY_SIZE > n; n++) {
			if (freq_tables[i][0] == (pAsv_Table->Mhz[n]*1000)) {
				freq_tables[i][1] = pAsv_Table->uV[n];
				break;
			}
		}
	}
	printk("DVFS:%s%ld%s\n", down?"-":"+", value, percent?"%":"mV");

	/* new voltage */
	for (i = 0; table_size > i; i++, al = 0) {
		uV = freq_tables[i][1];
		dv = percent ? ((uV/100) * value) : (value*1000);
		new = down ? uV - dv : uV + dv;

		#if defined (CONFIG_REGULATOR_MP8845C)
		new = find_uV(new);
		printk("%7ldkhz, %7ld (%s%ld) request %7ld -> %7ld\n",
			freq_tables[i][0], freq_tables[i][1],
			down?"-":"+", dv, (down ? uV - dv : uV + dv), new);
		#else
		if ((new % VOLTAGE_STEP_UV)) {
			new = (new / VOLTAGE_STEP_UV) * VOLTAGE_STEP_UV;
			al = 1;
			if (down) new += VOLTAGE_STEP_UV;	/* Upper */
		}
		printk("%7ldkhz, %7ld (%s%ld) align %d (%s) -> %7ld\n",
			freq_tables[i][0], freq_tables[i][1],
			down?"-":"+", dv, VOLTAGE_STEP_UV, al?"X":"O", new);
		#endif

		freq_tables[i][1] = new;
	}
	return 0;
}

static long s5p4418_asv_get_vol_margin(long uV, long value, bool down, bool percent)
{
	long step_vol = VOLTAGE_STEP_UV;
	long dv = percent ? ((uV/100) * value) : (value*1000);
	long new = down ? uV - dv : uV + dv;
	int al = 0;

	if (NULL == pAsv_Table)
		return -EINVAL;

	if ((new % step_vol)) {
		new = (new / step_vol) * step_vol;
		al = 1;
		if (down) new += step_vol;	/* Upper */
	}
	return new;
}

static int s5p4418_asv_current_label(char *buf)
{
	char *s = buf;

	if (NULL == pAsv_Table)
		return -EINVAL;

	if (s && pAsv_Table) {
		 if (!Asv_Param.flag) {
			s += sprintf(s, "%d:%dmA,%d\n",
					Asv_Param.level, Asv_Param.ids, Asv_Param.ro);
		} else {
			s += sprintf(s, "%d:G%d,S%d\n",
					Asv_Param.level, Asv_Param.group, Asv_Param.shift);
		}
	}
	return (s - buf);
}

static struct cpufreq_asv_ops asv_ops = {
	.setup_table = s5p4418_asv_setup_table,
	.get_voltage = s5p4418_asv_get_voltage,
	.modify_vol_table = s5p4418_asv_modify_vol_table,
	.current_label = s5p4418_asv_current_label,
	.get_vol_margin = s5p4418_asv_get_vol_margin,
};
#endif
