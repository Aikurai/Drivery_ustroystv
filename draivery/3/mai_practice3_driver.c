#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEVICE_NAME "mai_practice3_device"
#define CLASS_NAME "mai_practice3_class"

static dev_t dev_no;
static struct cdev dev;
static struct class *dev_class = NULL;
static struct device *device = NULL;

static int device_open(struct inode *inode, struct file *file) {
	pr_info("%s: trying to open the device\n", DEVICE_NAME);
	return 0;
}

static int device_release(struct inode *inode, struct file *file) {
	pr_info("%s: trying to release the device\n", DEVICE_NAME);
	return 0;
}

static struct file_operations fops = {
	.open = device_open,
	.release = device_release,
};

static int __init module_init_func(void) {
	int res;

	pr_info("Trying to initialize the driver\n");

	res = alloc_chrdev_region(&dev_no, 0, 1, DEVICE_NAME);
	if (res < 0) {
		pr_err("Failed to allocate chrdev region\n");
		return res;
	}

	cdev_init(&dev, &fops);
	res = cdev_add(&dev, dev_no, 1);
	if (res < 0) {
		pr_err("Failed to add cdev\n");
		unregister_chrdev_region(dev_no, 1);
		return res;
	}

	pr_info("Successfully initialized the driver\n");

	return 0;
}

static void __exit module_exit_func(void) {
	cdev_del(&dev);
	unregister_chrdev_region(dev_no, 1);
}

module_init(module_init_func);
module_exit(module_exit_func);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MAI Team");
MODULE_DESCRIPTION("MAI Practice 3 Driver");
