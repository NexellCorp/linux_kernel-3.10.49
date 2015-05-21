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
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dai.h>
#include <mach/platform.h>
#include "nxp-pcm.h"


#define pr_debug				printk


static char str_dai_name[16] = DEV_NAME_I2S;
static int (*cpu_resume_fn)(struct snd_soc_dai *dai) = NULL;

#define STUB_RATES		SNDRV_PCM_RATE_8000_192000
#define STUB_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

static struct snd_soc_codec_driver soc_codec_snd_null;
static struct snd_soc_codec_driver soc_codec_snd_null2;

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

static struct snd_soc_dai_driver null_stub_dai2 = {
	.name		= "snd-null-voice2",
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

/*
static int snd_null_codec_set_bias_level(struct snd_soc_codec *codec,
			enum snd_soc_bias_level level)
{
	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		break;

	case SND_SOC_BIAS_STANDBY:
		break;

	case SND_SOC_BIAS_OFF:
		break;

	default:
		break;
	}
	codec->dapm.bias_level = level;

	return 0;
}

static int snd_null_codec_probe(struct snd_soc_codec *codec)
{
	codec->dapm.bias_level = SND_SOC_BIAS_STANDBY;

	return 0;
}

static int snd_null_codec_remove(struct snd_soc_codec *codec)
{
	snd_null_codec_set_bias_level(codec, SND_SOC_BIAS_OFF);
	return 0;
}

#ifdef CONFIG_PM
static int snd_null_codec_suspend(struct snd_soc_codec *codec)
{
	snd_null_codec_set_bias_level(codec, SND_SOC_BIAS_OFF);
	return 0;
}

static int snd_null_codec_resume(struct snd_soc_codec *codec)
{
	if(codec->dapm.bias_level == SND_SOC_BIAS_ON) {
		snd_null_codec_set_bias_level(codec, SND_SOC_BIAS_ON);
	}
	else if(codec->dapm.bias_level == SND_SOC_BIAS_OFF) {
		snd_null_codec_set_bias_level(codec, SND_SOC_BIAS_STANDBY);
	}
	return 0;
}
#else
#define snd_null_codec_suspend NULL
#define snd_null_codec_resume NULL
#endif

static struct snd_soc_codec_driver soc_codec_snd_null = {
	.probe			= snd_null_codec_probe,
	.remove			= snd_null_codec_remove,
	.suspend	 	= snd_null_codec_suspend,
	.resume 		= snd_null_codec_resume,
	.set_bias_level = snd_null_codec_set_bias_level,
};
*/
static int snd_null_probe(struct platform_device *pdev)
{
	int ret;
	ret = snd_soc_register_codec(&pdev->dev, &soc_codec_snd_null,
			&null_stub_dai, 1);
	if(ret < 0)
		printk("snd null codec driver register fail.(ret=%d)\n", ret);

	ret = snd_soc_register_codec(&pdev->dev, &soc_codec_snd_null2,
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
 * SND-NULL Codec Driver
 */
static struct platform_driver snd_null_driver = {
	.probe			= snd_null_probe,
	.remove			= snd_null_remove,
	.driver			= {
		.name		= "snd-null",
		.owner		= THIS_MODULE,
	},
};

module_platform_driver(snd_null_driver);

MODULE_AUTHOR("jhkim <jhkim@nexell.co.kr>");
MODULE_DESCRIPTION("ASoc NULL driver");
MODULE_LICENSE("GPL");

/*
 * SND-NULL Card DAI
 */

//static struct snd_soc_codec *snd_null = NULL;
//static int codec_bias_level = 0;

static int snd_null_resume_pre(struct snd_soc_card *card)
{
	struct snd_soc_dai *cpu_dai = card->rtd->cpu_dai;
//	struct snd_soc_codec *codec = snd_null;

	int ret = 0;
	PM_DBGOUT("+%s\n", __func__);
	printk("+%s\n", __func__);

	/*
	 * first execute cpu(i2s) resume and execute codec resume.
	 */
	if (cpu_dai->driver->resume && ! cpu_resume_fn) {
		cpu_resume_fn  = cpu_dai->driver->resume;
//		cpu_dai->driver->resume = NULL;
	}

	cpu_dai->driver->resume = NULL;

	if (cpu_resume_fn)
		ret = cpu_resume_fn(cpu_dai);

//	PM_DBGOUT("%s BAIAS=%d\n", __func__, codec->dapm.bias_level);
//	codec_bias_level = codec->dapm.bias_level;

	return ret;
}

static int snd_null_resume_pre2(struct snd_soc_card *card)
{
	struct snd_soc_dai *cpu_dai = card->rtd->cpu_dai;
//	struct snd_soc_codec *codec = snd_null;

	int ret = 0;
	PM_DBGOUT("+%s\n", __func__);
	printk("+%s\n", __func__);

	/*
	 * first execute cpu(i2s) resume and execute codec resume.
	 */
	if (cpu_dai->driver->resume && ! cpu_resume_fn) {
		cpu_resume_fn  = cpu_dai->driver->resume;
//		cpu_dai->driver->resume = NULL;
	}

	cpu_dai->driver->resume = NULL;

	if (cpu_resume_fn)
		ret = cpu_resume_fn(cpu_dai);

//	PM_DBGOUT("%s BAIAS=%d\n", __func__, codec->dapm.bias_level);
//	codec_bias_level = codec->dapm.bias_level;

	return ret;
}

static int snd_null_resume_post(struct snd_soc_card *card)
{
//	struct snd_soc_codec *codec = snd_null;
	PM_DBGOUT("%s BAIAS=%d\n", __func__, codec->dapm.bias_level);
	printk("+%s\n", __func__);

//	if (SND_SOC_BIAS_OFF != codec_bias_level)
//		codec->driver->resume(codec);

	return 0;
}

static int snd_null_resume_post2(struct snd_soc_card *card)
{
//	struct snd_soc_codec *codec = snd_null;
	PM_DBGOUT("%s BAIAS=%d\n", __func__, codec->dapm.bias_level);
	printk("+%s\n", __func__);

//	if (SND_SOC_BIAS_OFF != codec_bias_level)
//		codec->driver->resume(codec);

	return 0;
}


static int snd_null_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_codec *codec = rtd->codec;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	printk("============%s %d\n", __func__, codec->id); 

//	snd_null = codec;

	if (cpu_dai->driver->resume && ! cpu_resume_fn) {
		cpu_resume_fn  = cpu_dai->driver->resume;
	}

	return 0;
}

static int snd_null_dai_init2(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_codec *codec = rtd->codec;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	printk("============%s %d\n", __func__, codec->id); 

//	snd_null = codec;

	if (cpu_dai->driver->resume && ! cpu_resume_fn) {
		cpu_resume_fn  = cpu_dai->driver->resume;
	}

	return 0;
}

static struct snd_soc_dai_link snd_null_dai_link = {
	.name 			= "ASoc-NULL",
	.stream_name 	= "Null Voice",
	.cpu_dai_name 	= str_dai_name,
	.platform_name  = DEV_NAME_PCM,			/* nxp_snd_pcm_driver name */
	.codec_dai_name = "snd-null-voice",
	.codec_name 	= "snd-null",
	.symmetric_rates = 1,
	.init			= snd_null_dai_init,
};

static struct snd_soc_dai_link snd_null_dai_link2 = {
	.name 			= "ASoc-NULL",
	.stream_name 	= "Null Voice",
	.cpu_dai_name 	= str_dai_name,
	.platform_name  = DEV_NAME_PCM,			/* nxp_snd_pcm_driver name */
	.codec_dai_name = "snd-null-voice",
	.codec_name 	= "snd-null",
	.symmetric_rates = 1,
	.init			= snd_null_dai_init2,
};

static struct snd_soc_card snd_null_card[] = {
	{
	.name 			= "SND-NULL.0",	/* proc/asound/cards */
	.dai_link 		= &snd_null_dai_link,
	.num_links 		= 1,
	.resume_pre		= &snd_null_resume_pre,
	.resume_post	= &snd_null_resume_post,
	},
	{
	.name 			= "SND-NULL.1",	/* proc/asound/cards */
	.dai_link 		= &snd_null_dai_link,
	.num_links 		= 1,
	},
	{
	.name 			= "SND-NULL.2",	/* proc/asound/cards */
	.dai_link 		= &snd_null_dai_link2,
	.num_links 		= 1,
	.resume_pre		= &snd_null_resume_pre2,
	.resume_post	= &snd_null_resume_post2,
	},
};

static int snd_card_probe(struct platform_device *pdev)
{
	struct nxp_snd_dai_plat_data *plat = pdev->dev.platform_data;
	struct snd_soc_card *card = &snd_null_card[0];
	struct snd_soc_dai_driver *cpudrv = NULL;
	unsigned int rates = 0, format = 0;
	int ret;

	/* set I2S name */
	if (plat)
		sprintf(str_dai_name, "%s.%d", DEV_NAME_I2S, plat->i2s_ch);

	if (pdev->id != -1)
		card = &snd_null_card[pdev->id];

	card->dev = &pdev->dev;
	ret = snd_soc_register_card(card);
	printk("-====================-%s.%d %d\n", __func__, pdev->id, ret);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n", ret);
		return ret;
	}

	if (plat) {
		rates = plat->sample_rate;
		format = plat->pcm_format;
	}

	if (card->rtd) {
		struct snd_soc_dai *cpu_dai = card->rtd->cpu_dai;
		if (cpu_dai)
			cpudrv = cpu_dai->driver;
	}
	pr_debug("snd-null-dai: register card %s -> %s\n",
		card->dai_link->codec_dai_name, card->dai_link->cpu_dai_name);

	if (NULL == cpudrv)
		return 0;

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

	return ret;
}

static int snd_card_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	snd_soc_unregister_card(card);
	return 0;
}

static struct platform_driver snd_card_driver = {
	.driver		= {
		.name	= "snd-null-card",
		.owner	= THIS_MODULE,
		.pm 	= &snd_soc_pm_ops,	/* for suspend */
	},
	.probe		= snd_card_probe,
	.remove		= snd_card_remove,
};
module_platform_driver(snd_card_driver);

MODULE_AUTHOR("jhkim <jhkim@nexell.co.kr>");
MODULE_DESCRIPTION("Sound codec-null driver for the SLSI");
MODULE_LICENSE("GPL");

