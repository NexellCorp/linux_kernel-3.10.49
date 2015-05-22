#include <linux/slab.h> //many add
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/vmalloc.h>
#include <linux/completion.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <media/v4l2-device.h>
#include <media/v4l2-subdev.h>

#include "thp7212-nx.h"

#define CONFIG_VIDEO_THP7212_V_1_1

#include "thp7212-nx-preset.h"
#include "thp7212_regs_1_1.h"

struct thp7212_state {
	struct media_pad	 	pad; /* for media deivce pad */
	struct v4l2_subdev 		sd;
};

#define I2C_RETRY_COUNT     10
#define POLL_TIME_MS        10

/*static int thp7212_i2c_read_data(struct i2c_client *client, unsigned int _addr, unsigned char *_data, unsigned int _size)*/
/*{*/
    /*struct i2c_adapter *adap = client->adapter;*/
    /*int	cnt;*/
    /*unsigned char _reg[2] = {0};*/

    /*struct i2c_msg msgs[] = {*/
        /*{*/
            /*.addr = client->addr,*/
            /*.flags = 0,*/
            /*.len = 2,*/
            /*.buf = _reg,*/
        /*},*/
        /*{*/
            /*.addr = client->addr,*/
            /*.flags = I2C_M_RD,*/
            /*.len = _size,*/
            /*.buf = _data,*/
        /*}*/
    /*};*/

    /*_reg[0] = (unsigned char)(_addr>>8);*/
    /*_reg[1] = (unsigned char)_addr;*/

    /*for (cnt = 0; cnt < I2C_RETRY_COUNT; cnt++) {*/
        /*if (i2c_transfer(adap, msgs, 2) == 2)*/
            /*break;*/
        /*mdelay(10);*/
    /*}*/

    /*if (cnt == I2C_RETRY_COUNT) {*/
        /*printk(KERN_ERR "soc_i2c_read retry\n");*/
        /*return -1;*/
    /*}*/

    /*return 0;*/
/*}*/

/*static int thp7212_i2c_read_byte(struct i2c_client *client, u8 addr, u8 *data)*/
/*{*/
    /*s8 i = 0;*/
    /*s8 ret = 0;*/
    /*u8 buf = 0;*/
    /*struct i2c_msg msg[2];*/

    /*msg[0].addr = client->addr;*/
    /*msg[0].flags = 0;*/
    /*msg[0].len = 1;*/
    /*msg[0].buf = &addr;*/

    /*msg[1].addr = client->addr;*/
    /*msg[1].flags = I2C_M_RD;*/
    /*msg[1].len = 1;*/
    /*msg[1].buf = &buf;*/

    /*for(i=0; i<I2C_RETRY_COUNT; i++) {*/
        /*ret = i2c_transfer(client->adapter, msg, 2);*/
        /*if (likely(ret == 2))*/
            /*break;*/
        /*mdelay(POLL_TIME_MS);*/
        /*//dev_err(&client->dev, "\e[31mthp7212_i2c_write_byte failed reg:0x%02x retry:%d\e[0m\n", addr, i);*/
    /*}*/

    /*if (unlikely(ret != 2))*/
    /*{*/
        /*dev_err(&client->dev, "\e[31mthp7212_i2c_read_byte failed reg:0x%02x \e[0m\n", addr);*/
        /*return -EIO;*/
    /*}*/

    /**data = buf;*/
    /*return 0;*/
/*}*/

/*static int thp7212_i2c_write_byte(struct i2c_client *client, u8 addr, u8 val)*/
/*{*/
    /*s8 i = 0;*/
    /*s8 ret = 0;*/
    /*u8 buf[2];*/
    /*u8 read_val = 0;*/
    /*struct i2c_msg msg;*/

    /*msg.addr = client->addr;*/
    /*msg.flags = 0;*/
    /*msg.len = 2;*/
    /*msg.buf = buf;*/

    /*buf[0] = addr;*/
    /*buf[1] = val ;*/

    /*for(i=0; i<I2C_RETRY_COUNT; i++) {*/
        /*ret = i2c_transfer(client->adapter, &msg, 1);*/
        /*if (likely(ret == 1))*/
            /*break;*/
        /*mdelay(POLL_TIME_MS);*/
        /*//dev_err(&client->dev, "\e[31mthp7212_i2c_write_byte failed reg:0x%02x write:0x%04x, retry:%d\e[0m\n", addr, val i);*/
    /*}*/

    /*if (ret != 1) {*/
        /*thp7212_i2c_read_byte(client, addr, &read_val);*/
        /*dev_err(&client->dev, "\e[31mthp7212_i2c_write_byte failed reg:0x%02x write:0x%04x, read:0x%04x, retry:%d\e[0m\n", addr, val, read_val, i);*/
        /*return -EIO;*/
    /*}*/

    /*return 0;*/
/*}*/

static int thp7212_i2c_write_block(struct v4l2_subdev *sd, u8 *buf, int size)
{
    struct i2c_client *client = v4l2_get_subdevdata(sd);
    s8 i = 0;
    s8 ret = 0;
    struct i2c_msg msg;

    msg.addr = client->addr;
    msg.flags = 0;
    msg.len = size;
    msg.buf = buf;

    for(i=0; i<I2C_RETRY_COUNT; i++) {
        ret = i2c_transfer(client->adapter, &msg, 1);
        if (likely(ret == 1))
            break;
        msleep(POLL_TIME_MS);
    }

    if (ret != 1) {
        dev_err(&client->dev, "\e[31mthp7212_i2c_write_block failed size:%d \e[0m\n", size);
        return -EIO;
    }

    return 0;
}

static int thp7212_s_power(struct v4l2_subdev *sd, int on)
{
    return 0;
}

static int thp7212_init(struct v4l2_subdev *sd, u32 val)
{
    struct i2c_client *client = v4l2_get_subdevdata(sd);
    /*struct thp7212_state *state = container_of(sd, struct thp7212_state, sd);*/
    int ret = 0;

    // Start C0 00 00 ram_7210.elf.s19.1 Stop
    ret = thp7212_i2c_write_block(sd, ram_7210_elf_s19_1, sizeof(ram_7210_elf_s19_1));
    if(ret < 0) {
        dev_err(&client->dev, "\e[31m%s(ram_7210_elf_s19_1) i2c error\e[0m, ret = %d\n", __func__, ret);
        return ret;
    }
    // Start C0 FF 08 10 00 80 Stop
    {
        u8 buf[] = { 0xFF, 0x08, 0x10, 0x00, 0x80 };
        ret = thp7212_i2c_write_block(sd, buf, sizeof(buf));
        if(ret < 0) {
            dev_err(&client->dev, "\e[31m%s(Start C0 FF 08 10 00 80 Stop) i2c error\e[0m, ret = %d\n", __func__, ret);
            return ret;
        }
    }

    // Start C0 00 00 ram_7210.elf.s19.2 Stop
    ret = thp7212_i2c_write_block(sd, ram_7210_elf_s19_2, sizeof(ram_7210_elf_s19_2));
    if(ret < 0) {
        dev_err(&client->dev, "\e[31m%s(ram_7210_elf_s19_2) i2c error\e[0m, ret = %d\n", __func__, ret);
        return ret;
    }
    // Start C0 FF 08 10 01 00 Stop
    {
        u8 buf[] = { 0xFF, 0x08, 0x10, 0x01, 0x00 };
        mdelay(100);
        ret = thp7212_i2c_write_block(sd, buf, sizeof(buf));
        if(ret < 0) {
            dev_err(&client->dev, "\e[31m%s( Start C0 FF 08 10 01 00 Stop ) i2c error\e[0m, ret = %d\n", __func__, ret);
            return ret;
        }
    }

    // Start C0 00 00 ram_7210.elf.s19.3 Stop
    ret = thp7212_i2c_write_block(sd, ram_7210_elf_s19_3, sizeof(ram_7210_elf_s19_3));
    if(ret < 0) {
        dev_err(&client->dev, "\e[31m%s(ram_7210_elf_s19_3) i2c error\e[0m, ret = %d\n", __func__, ret);
        return ret;
    }

    // Start C0 FF 00 01 Stop
    {
        u8 buf[] = { 0xFF, 0x00, 0x01 };
        ret = thp7212_i2c_write_block(sd, buf, sizeof(buf));
        if(ret < 0) {
            dev_err(&client->dev, "\e[31m%s(Start C0 FF 00 01 Stop) i2c error\e[0m, ret = %d\n", __func__, ret);
            return ret;
        }
    }

    mdelay(100);
    // Start C0 F0 1C 0x Stop
    {
        u8 buf[] = { 0xF0, 0x1C, 0x00 }; //Frame rate select 0x00-0x02 (0x00:30fps, 0x01:25fps, 0x02:20fps)
        ret = thp7212_i2c_write_block(sd, buf, sizeof(buf));
        if(ret < 0) {
            dev_err(&client->dev, "\e[31m%s(Start C0 F0 1C 0x Stop) i2c error\e[0m, ret = %d\n", __func__, ret);
            return ret;
        }
    }

    mdelay(100);
    // Start C0 F0 0B 01 Stop
    {
        u8 buf[] = { 0xF0, 0x0B, 0x01 }; //	Output ON/OFF 0x00-0x01 (0x00:OFF, 0x01:ON)
        ret = thp7212_i2c_write_block(sd, buf, sizeof(buf));
        if(ret < 0) {
            dev_err(&client->dev, "\e[31m%s(Start C0 F0 0B 01 Stop) i2c error\e[0m, ret = %d\n", __func__, ret);
            return ret;
        }
    }

    return 0;
}

static int thp7212_restart(struct v4l2_subdev *sd)
{
    struct i2c_client *client = v4l2_get_subdevdata(sd);
    /*struct thp7212_state *state = container_of(sd, struct thp7212_state, sd);*/

    int ret = 0;

    // Start C0 FF 00 01 Stop
    {
        u8 buf[] = { 0xFF, 0x00, 0x01 };
        ret = thp7212_i2c_write_block(sd, buf, sizeof(buf));
        if(ret < 0) {
            dev_err(&client->dev, "\e[31m%s(Start C0 FF 00 01 Stop) i2c error\e[0m, ret = %d\n", __func__, ret);
            return ret;
        }
    }

    mdelay(100);
    // Start C0 F0 1C 0x Stop
    {
        u8 buf[] = { 0xF0, 0x1C, 0x00 }; //Frame rate select 0x00-0x02 (0x00:30fps, 0x01:25fps, 0x02:20fps)
        ret = thp7212_i2c_write_block(sd, buf, sizeof(buf));
        if(ret < 0) {
            dev_err(&client->dev, "\e[31m%s(Start C0 F0 1C 0x Stop) i2c error\e[0m, ret = %d\n", __func__, ret);
            return ret;
        }
    }

    mdelay(100);
    // Start C0 F0 0B 01 Stop
    {
        u8 buf[] = { 0xF0, 0x0B, 0x01 }; //	Output ON/OFF 0x00-0x01 (0x00:OFF, 0x01:ON)
        ret = thp7212_i2c_write_block(sd, buf, sizeof(buf));
        if(ret < 0) {
            dev_err(&client->dev, "\e[31m%s(Start C0 F0 0B 01 Stop) i2c error\e[0m, ret = %d\n", __func__, ret);
            return ret;
        }
    }

    dev_err(&client->dev, "%s: end\n", __func__);

    return 0;
}

static bool camera_initialized = false;
static int thp7212_s_stream(struct v4l2_subdev *sd, int enable)
{
    /* struct i2c_client *client = v4l2_get_subdevdata(sd); */
    /*struct thp7212_state *state = container_of(sd, struct thp7212_state, sd);*/

    if (enable) {
        //added by keun 2015.05.07
        if( !camera_initialized ) {
            printk(KERN_INFO "Camera FW Initialization....!!!\n");
            thp7212_init(sd, enable);
            camera_initialized = true;
        } else {
            printk(KERN_INFO "Camera FW is already initialized....!!!\n");
            thp7212_restart(sd);
        }
    } else {
    }

    return 0;
}

static int thp7212_set_fmt(struct v4l2_subdev *sd, struct v4l2_subdev_fh *fh,
        struct v4l2_subdev_format *fmt)
{
    return 0;
}

static const struct v4l2_subdev_core_ops thp7212_core_ops = {
    .s_power    = thp7212_s_power,
};

static const struct v4l2_subdev_video_ops thp7212_video_ops = {
    .s_stream   = thp7212_s_stream,
};

static struct v4l2_subdev_pad_ops thp7212_pad_ops = {
    .set_fmt    = thp7212_set_fmt,
};

static const struct v4l2_subdev_ops thp7212_ops = {
    .core       = &thp7212_core_ops,
    .video      = &thp7212_video_ops,
    .pad        = &thp7212_pad_ops,
};

static int thp7212_probe(struct i2c_client *client,
        const struct i2c_device_id *id)
{
    struct v4l2_subdev *sd;
    struct thp7212_state *state;
    int ret = 0;

    state = kzalloc(sizeof(struct thp7212_state), GFP_KERNEL);
    if (state == NULL)
        return -ENOMEM;

    sd = &state->sd;
    strcpy(sd->name, THP7212_DRIVER_NAME);

    v4l2_i2c_subdev_init(sd, client, &thp7212_ops);
    state->pad.flags = MEDIA_PAD_FL_SOURCE;
    ret = media_entity_init(&sd->entity, 1, &state->pad, 0);
    if (ret < 0) {
        dev_err(&client->dev, "%s: failed\n", __func__);
        return ret;
    }

    sd->entity.type = MEDIA_ENT_T_V4L2_SUBDEV_SENSOR;
    sd->flags = V4L2_SUBDEV_FL_HAS_DEVNODE;

    printk("13MP camera THP7212 loaded.\n");

    return 0;
}

static int thp7212_remove(struct i2c_client *client)
{
    struct v4l2_subdev *sd = i2c_get_clientdata(client);
    struct thp7212_state *state =
        container_of(sd, struct thp7212_state, sd);

    v4l2_device_unregister_subdev(sd);
    kfree(state);

    return 0;
}

static const struct i2c_device_id thp7212_id[] = {
    { THP7212_DRIVER_NAME, 0 },
    {}
};

MODULE_DEVICE_TABLE(i2c, thp7212_id);

static struct i2c_driver thp7212_i2c_driver = {
    .driver = {
        .name = THP7212_DRIVER_NAME,
    },
    .probe = thp7212_probe,
    .remove = thp7212_remove,
    .id_table = thp7212_id,
};

static int __init thp7212_mod_init(void)
{
    return i2c_add_driver(&thp7212_i2c_driver);
}

static void __exit thp7212_mod_exit(void)
{
    i2c_del_driver(&thp7212_i2c_driver);
}

module_init(thp7212_mod_init);
module_exit(thp7212_mod_exit);


MODULE_DESCRIPTION("THP7212 camera driver");
MODULE_AUTHOR("   <    @nexell.co.kr>");
MODULE_LICENSE("GPL");
