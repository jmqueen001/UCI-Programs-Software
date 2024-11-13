#include <linux/init.h>
#include <linux/module.h>

int DeviceDriver_init(void)
{
	printk(KERN_ALERT "Inside the %s function\n", _FUNCTION_);
	return 0;
}

void DeviceDriver_exit(void)
{
	printk(KERN_ALERT "Inside the %s fucntion\n", _FUNCTION_);

}

module_init(DeviceDriver_init);
module_exit(DeviceDriver_exit);


