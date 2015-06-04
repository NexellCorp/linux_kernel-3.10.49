#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/platform_device.h>

#include <nexell/platform.h>

/*
#define	pr_debug	printk
*/
static inline int wait_key_ready(void)
{
	unsigned long timeout = jiffies + 1;

	while (!NX_ECID_GetKeyReady()) {
		if (time_after(jiffies, timeout)) {
			if (NX_ECID_GetKeyReady())
				return 0;
			pr_err("Error: id not key ready \n");
			break;
		}
		cpu_relax();
	}
	return -EINVAL;
}

int nxp_cpu_id_guid(u32 guid[4])
{
	if (0 > wait_key_ready())
		return -EINVAL;
	NX_ECID_GetGUID((NX_GUID*)guid);
	return 0;
}

int nxp_cpu_id_ecid(u32 ecid[4])
{
	if (0 > wait_key_ready())
		return -EINVAL;
	NX_ECID_GetECID(ecid);
	return 0;
}

int nxp_cpu_id_string(u32 *string)
{
	if (0 > wait_key_ready())
		return -EINVAL;
	NX_ECID_GetChipName((char*)string);
	return 0;
}

/* Notify cpu GUID: /sys/devices/platform/cpu,  guid, uuid,  name  */
static ssize_t sys_id_show(struct device *pdev,
					struct device_attribute *attr, char *buf)
{
	struct attribute *at = &attr->attr;
	char *s = buf;
	u32 uid[4] = {0, };
	u8  name[12*4] = {0,};
	int string = -EINVAL;

	pr_debug("[%s : name =%s ]\n", __func__, at->name);

	if (!strcmp(at->name, "uuid"))
		nxp_cpu_id_ecid(uid);
	else
	if (!strcmp(at->name, "guid"))
		nxp_cpu_id_guid(uid);
	else
	if (!strcmp(at->name, "name"))
		string = nxp_cpu_id_string((u32*)name);
	else
		return -EINVAL;

	if (!string)
		s += sprintf(s, "%s\n", name);
	else
		s += sprintf(s, "%08x:%08x:%08x:%08x\n", uid[0], uid[1], uid[2], uid[3]);

	if (s != buf)
		*(s-1) = '\n';


	return (s - buf);
}

#define	ATTR_MODE	0644
static struct device_attribute __guid__ = __ATTR(guid, ATTR_MODE, sys_id_show, NULL);
static struct device_attribute __uuid__ = __ATTR(uuid, ATTR_MODE, sys_id_show, NULL);
static struct device_attribute __name__ = __ATTR(name, ATTR_MODE, sys_id_show, NULL);

static struct attribute *sys_attrs[] = {
	&__guid__.attr,
	&__uuid__.attr,
	&__name__.attr,
	NULL,
};

static struct attribute_group sys_attr_group = {
	.attrs = (struct attribute **)sys_attrs,
};

static int __init cpu_sys_init_setup(void)
{
	struct kobject *kobj = kobject_create_and_add("cpu", &platform_bus.kobj);
	int ret = 0;

	if (!kobj) {
		pr_err("Failed create cpu kernel object ....\n");
		return -ret;
	}

	ret = sysfs_create_group(kobj, &sys_attr_group);
	if (ret) {
		pr_err("Failed create cpu sysfs group ...\n");
		kobject_del(kobj);
		return -ret;
	}
	return ret;
}
core_initcall(cpu_sys_init_setup);
