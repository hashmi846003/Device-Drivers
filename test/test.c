#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init desd_init(void)
{
    printk(KERN_INFO "%s : init is successful\n", THIS_MODULE->name);
    return 0;
}

static void __exit desd_exit(void)
{
    printk(KERN_INFO "%s : desd_exit : exit is successful\n", THIS_MODULE->name);
}

module_init(desd_init);
module_exit(desd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hashmi");
MODULE_DESCRIPTION("This is eldd");
