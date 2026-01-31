// pcd.c - Pseudo Character Driver (Multi-node)
// Compatible with Linux kernel 6.x+

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DRIVER_NAME     "pcd"
#define CLASS_NAME      "pcd_class"
#define DEVICE_COUNT    4
#define BUFFER_SIZE     512

/* Device private data */
struct pcd_dev {
    char buffer[BUFFER_SIZE];
    struct cdev cdev;
};

static dev_t dev_num;
static struct class *pcd_class;
static struct pcd_dev pcd_devices[DEVICE_COUNT];

/* ---------- File Operations ---------- */

static int pcd_open(struct inode *inode, struct file *filp)
{
    struct pcd_dev *dev;

    dev = container_of(inode->i_cdev, struct pcd_dev, cdev);
    filp->private_data = dev;

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
    struct pcd_dev *dev = filp->private_data;

    if (*f_pos >= BUFFER_SIZE)
        return 0;

    if (count > BUFFER_SIZE - *f_pos)
        count = BUFFER_SIZE - *f_pos;

    if (copy_to_user(buf, dev->buffer + *f_pos, count))
        return -EFAULT;

    *f_pos += count;
    return count;
}

static ssize_t pcd_write(struct file *filp, const char __user *buf,
                         size_t count, loff_t *f_pos)
{
    struct pcd_dev *dev = filp->private_data;

    if (*f_pos >= BUFFER_SIZE)
        return -ENOMEM;

    if (count > BUFFER_SIZE - *f_pos)
        count = BUFFER_SIZE - *f_pos;

    if (copy_from_user(dev->buffer + *f_pos, buf, count))
        return -EFAULT;

    *f_pos += count;
    return count;
}

static const struct file_operations pcd_fops = {
    .owner   = THIS_MODULE,
    .open    = pcd_open,
    .release = pcd_release,
    .read    = pcd_read,
    .write   = pcd_write,
};

/* ---------- Module Init / Exit ---------- */

static int __init pcd_init(void)
{
    int ret, i;

    /* Allocate device numbers */
    ret = alloc_chrdev_region(&dev_num, 0, DEVICE_COUNT, DRIVER_NAME);
    if (ret)
        return ret;

    /* Create device class (NEW API) */
    pcd_class = class_create(CLASS_NAME);
    if (IS_ERR(pcd_class)) {
        unregister_chrdev_region(dev_num, DEVICE_COUNT);
        return PTR_ERR(pcd_class);
    }

    /* Initialize devices */
    for (i = 0; i < DEVICE_COUNT; i++) {
        cdev_init(&pcd_devices[i].cdev, &pcd_fops);
        pcd_devices[i].cdev.owner = THIS_MODULE;

        ret = cdev_add(&pcd_devices[i].cdev, dev_num + i, 1);
        if (ret)
            goto cleanup;

        device_create(pcd_class, NULL,
                      dev_num + i, NULL,
                      DRIVER_NAME "%d", i);
    }

    pr_info("pcd: module loaded\n");
    return 0;

cleanup:
    while (i--) {
        device_destroy(pcd_class, dev_num + i);
        cdev_del(&pcd_devices[i].cdev);
    }

    class_destroy(pcd_class);
    unregister_chrdev_region(dev_num, DEVICE_COUNT);
    return ret;
}

static void __exit pcd_exit(void)
{
    int i;

    for (i = 0; i < DEVICE_COUNT; i++) {
        device_destroy(pcd_class, dev_num + i);
        cdev_del(&pcd_devices[i].cdev);
    }

    class_destroy(pcd_class);
    unregister_chrdev_region(dev_num, DEVICE_COUNT);

    pr_info("pcd: module unloaded\n");
}

module_init(pcd_init);
module_exit(pcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hashmi");
MODULE_DESCRIPTION("Pseudo Character Driver with multiple device nodes");
MODULE_VERSION("1.0");
