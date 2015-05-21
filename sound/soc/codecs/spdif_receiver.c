/*
 * ALSA SoC SPDIF DIR (Digital Interface Reciever) driver
 *
 * Based on ALSA SoC SPDIF DIT driver
 *
 *  This driver is used by controllers which can operate in DIR (SPDI/F) where
 *  no codec is needed.  This file provides stub codec that can be used
 *  in these configurations. SPEAr SPDIF IN Audio controller uses this driver.
 *
 * Author:      Vipin Kumar,  <vipin.kumar@st.com>
 * Copyright:   (C) 2012  ST Microelectronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/of.h>

#include <sound/soc.h>
#include <sound/pcm.h>
#include <sound/initval.h>

#define STUB_RATES	SNDRV_PCM_RATE_8000_96000
#define STUB_FORMATS	SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE

static struct snd_soc_codec_driver soc_codec_spdif_dir;

static struct snd_soc_dai_driver dir_stub_dai = {
	.name		= "dir-hifi",
	.capture	= {
		.stream_name	= "Capture",
		.channels_min	= 1,
		.channels_max	= 384,
		.rates		= STUB_RATES,
		.formats	= STUB_FORMATS,
	},
};

static int spdif_dir_probe(struct platform_device *pdev)
{
    int ret = snd_soc_register_codec(&pdev->dev, &soc_codec_spdif_dir,
            &dir_stub_dai, 1); 
    if (ret < 0)
        printk("snd spdif-dir register fail.(ret=%d)\n", ret);

    return ret;
}

static int spdif_dir_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id nxp_spdif_dir_match[] = {
        { .compatible = "nexell,spdif-dir" },
            {},
};
MODULE_DEVICE_TABLE(of, nxp_spdif_dir_match);
#else
#define nxp_spdif_dir_match NULL
#endif

static struct platform_driver spdif_dir_driver = {
	.probe		= spdif_dir_probe,
	.remove		= spdif_dir_remove,
	.driver		= {
		.name	= "spdif-dir",
		.owner	= THIS_MODULE,
        .of_match_table = of_match_ptr(nxp_spdif_dir_match),
	},
};

module_platform_driver(spdif_dir_driver);

MODULE_DESCRIPTION("ASoC SPDIF DIR driver");
MODULE_AUTHOR("Vipin Kumar <vipin.kumar@st.com>");
MODULE_LICENSE("GPL");
