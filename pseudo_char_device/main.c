#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEV_MEM_SIZE 512

char char_device_buffer[DEV_MEM_SIZE];

dev_t device_number;
struct cdev pcd_cdev;


static int pcd_open(struct inode *inode, struct file *filp);
static int pcd_release(struct inode *inode, struct file *filp);
static ssize_t pcd_read(struct file *filp, char __user *buf,
                        size_t count, loff_t *f_pos);
static ssize_t pcd_write(struct file *filp, const char __user *buf,
                         size_t count, loff_t *f_pos);


struct file_operations pcd_fops = {
    .owner   = THIS_MODULE,
    .open    = pcd_open,
    .release = pcd_release,
    .read    = pcd_read,
    .write   = pcd_write,
};


static int pcd_open(struct inode *inode, struct file *filp)
{
    pr_info("pcd: device opened\n");
    return 0;
}

static int pcd_release(struct inode *inode, struct file *filp)
{
    pr_info("pcd: device closed\n");
    return 0;
}

static ssize_t pcd_read(struct file *filp, char __user *buf,
                        size_t count, loff_t *f_pos)
{
    if (*f_pos >= DEV_MEM_SIZE)
        return 0;

    if ((*f_pos + count) > DEV_MEM_SIZE)
        count = DEV_MEM_SIZE - *f_pos;

    if (copy_to_user(buf, char_device_buffer + *f_pos, count))
        return -EFAULT;

    *f_pos += count;
    pr_info("pcd: read %zu bytes\n", count);
    return count;
}

static ssize_t pcd_write(struct file *filp, const char __user *buf,
                         size_t count, loff_t *f_pos)
{
    if (*f_pos >= DEV_MEM_SIZE)
        return -ENOMEM;

    if ((*f_pos + count) > DEV_MEM_SIZE)
        count = DEV_MEM_SIZE - *f_pos;

    if (copy_from_user(char_device_buffer + *f_pos, buf, count))
        return -EFAULT;

    *f_pos += count;
    pr_info("pcd: wrote %zu bytes\n", count);
    return count;
}


static int __init pcd_module_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&device_number, 0, 1, "pcd");
    if (ret < 0) {
        pr_err("pcd: device number allocation failed\n");
        return ret;
    }

    cdev_init(&pcd_cdev, &pcd_fops);
    pcd_cdev.owner = THIS_MODULE;

    ret = cdev_add(&pcd_cdev, device_number, 1);
    if (ret < 0) {
        unregister_chrdev_region(device_number, 1);
        return ret;
    }

    pr_info("pcd: module loaded\n");
    pr_info("pcd: Major = %d Minor = %d\n",
            MAJOR(device_number), MINOR(device_number));

    return 0;
}


static void __exit pcd_module_cleanup(void)
{
    cdev_del(&pcd_cdev);
    unregister_chrdev_region(device_number, 1);
    pr_info("pcd: module unloaded\n");
}

module_init(pcd_module_init);
module_exit(pcd_module_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hashmi");
MODULE_DESCRIPTION("Pseudo Character Device");
