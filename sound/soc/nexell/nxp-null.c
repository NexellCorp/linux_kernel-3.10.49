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

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>

#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dai.h>

#include <nexell/soc-s5pxx18.h>

#include "nxp-pcm.h"

#define I2S_BASEADDR            PHYS_BASE_I2S0
#define I2S_CH_OFFSET           0x1000

static char str_dai_name[16] = "c0055000.i2s";

#define STUB_RATES		SNDRV_PCM_RATE_8000_192000
#define STUB_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

static struct snd_soc_codec_driver soc_codec_snd_null;

static struct snd_soc_dai_driver null_stub_dai = {
	.name		= "snd-null-voice",
	.playback 	= {
		.stream_name	= "Null Playback",
		.channels_min	= 1,
		.channels_max	= 2,
		.rates			= STUB_RATES,
		.formats		= STUB_FORMATS,
	},
	.capture 	= {
		.stream_name	= "Null Capture",
		.channels_min	= 1,
		.channels_max	= 2,
		.rates			= STUB_RATES,
		.formats		= STUB_FORMATS,
	},
};

static int snd_null_probe(struct platform_device *pdev)
{
	int ret = snd_soc_register_codec(&pdev->dev, &soc_codec_snd_null,
			&null_stub_dai, 1);
	if(ret < 0)
		printk("snd null codec driver register fail.(ret=%d)\n", ret);
	return ret;
}

static int snd_null_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

/*
 * SND-NULL Receiver
 */

#ifdef CONFIG_OF
static const struct of_device_id snd_null_match[] = { 
	        { .compatible = "nexell,snd-null" },
			            {},
};
MODULE_DEVICE_TABLE(of, snd_null_match);
#else
#define snd_null_match NULL
#endif

static struct platform_driver snd_null_driver = {
	.probe		= snd_null_probe,
	.remove		= snd_null_remove,
	.driver		= {
		.name	= "snd-null",
		.owner	= THIS_MODULE,
        .of_match_table = of_match_ptr(snd_null_match),
	},
};

module_platform_driver(snd_null_driver);

MODULE_AUTHOR("jhkim <jhkim@nexell.co.kr>");
MODULE_DESCRIPTION("ASoc NULL driver");
MODULE_LICENSE("GPL");

/*
 * SND-NULL Card DAI
 */
static struct snd_soc_dai_link snd_null_dai_link = {
	.name 			= "ASoc-NULL",
	.stream_name 	= "Null Voice",
	.cpu_dai_name 	= str_dai_name,
	.platform_name  = "nxp-pcm",			/* nxp_snd_pcm_driver name */
	.codec_dai_name = "snd-null-voice",
	.codec_name 	= "0.snd-null",
	.symmetric_rates = 1,
};

static struct snd_soc_card snd_null_card[] = {
	{
	.name 			= "SND-NULL.0",	/* proc/asound/cards */
	.dai_link 		= &snd_null_dai_link,
	.num_links 		= 1,
	},
	{
	.name 			= "SND-NULL.1",	/* proc/asound/cards */
	.dai_link 		= &snd_null_dai_link,
	.num_links 		= 1,
	},
	{
	.name 			= "SND-NULL.2",	/* proc/asound/cards */
	.dai_link 		= &snd_null_dai_link,
	.num_links 		= 1,
	},
};

static int snd_card_probe(struct platform_device *pdev)
{
	struct nxp_snd_dai_plat_data *plat = pdev->dev.platform_data;
	struct snd_soc_card *card = &snd_null_card[0];
	struct snd_soc_dai_driver *cpudrv = NULL;
	unsigned int rates = 0, format = 0;
	int ret;
    int ch;

	/* set I2S name */

    of_property_read_u32(pdev->dev.of_node, "ch", &ch);
	sprintf(str_dai_name, "%x%s%d", (I2S_BASEADDR + (ch * I2S_CH_OFFSET)), ".i2s", ch);
	card = &snd_null_card[ch];

	card->dev = &pdev->dev;
	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n", ret);
		return ret;
	}
#if 0
	if (plat) {
		rates = plat->sample_rate;
		format = plat->pcm_format;
	}
#endif
	if (card->rtd) {
		struct snd_soc_dai *cpu_dai = card->rtd->cpu_dai;
		if (cpu_dai)
			cpudrv = cpu_dai->driver;
	}
	pr_debug("snd-null-dai: register card %s -> %s\n",
		card->dai_link->codec_dai_name, card->dai_link->cpu_dai_name);

	if (NULL == cpudrv)
		return 0;
#if 0
	/*
	 * Reset i2s sample rates
	 */
	if (rates) {
		rates = snd_pcm_rate_to_rate_bit(rates);
		if (SNDRV_PCM_RATE_KNOT == rates)
			printk("%s, invalid sample rates=%d\n", __func__, plat->sample_rate);
		else {
			cpudrv->playback.rates = rates;
			cpudrv->capture.rates = rates;
		}
	}

	/*
	 * Reset i2s format
	 */
	if (format) {
		cpudrv->playback.formats = format;
		cpudrv->capture.formats = format;
	}
#endif
	return ret;
}

static int snd_card_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	snd_soc_unregister_card(card);
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id snd_null_card_match[] = { 
	{ .compatible = "nexell,snd-null-card" },
	{},
};
MODULE_DEVICE_TABLE(of, snd_null_card_match);
#else
#define snd_null_card_match NULL
#endif

static struct platform_driver snd_card_driver = {
	.driver		= {
		.name	= "snd-null-card",
		.owner	= THIS_MODULE,
		.pm 	= &snd_soc_pm_ops,	/* for suspend */
        .of_match_table = of_match_ptr(snd_null_card_match),
	},
	.probe		= snd_card_probe,
	.remove		= snd_card_remove,
};
module_platform_driver(snd_card_driver);

MODULE_AUTHOR("jhkim <jhkim@nexell.co.kr>");
MODULE_DESCRIPTION("Sound codec-null driver for the SLSI");
MODULE_LICENSE("GPL");

