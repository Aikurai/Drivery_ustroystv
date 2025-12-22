#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/wait.h>

#define DEVICE_NAME "mai_practice4_device"
#define CLASS_NAME "mai_practice4_class"
#define BUFFER_SIZE 256
#define MAGIC_NUM 100

#define DRIVER_CLEAR_BUF _IO(MAGIC_NUM, 0)
#define DRIVER_BUF_IS_EMPTY _IOR(MAGIC_NUM, 1, int)

static dev_t dev_no;
static struct cdev dev;
static struct class *dev_class;
static struct device *device;

static char device_buffer[BUFFER_SIZE];
static size_t buffer_len = 0;
static struct mutex buffer_mutex;
static wait_queue_head_t read_queue;

static int device_open(struct inode *inode, struct file *file) {
    pr_info(DEVICE_NAME ": device_open: trying to open the device\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    pr_info(DEVICE_NAME ": device_release: trying to release the device\n");
    return 0;
}

static ssize_t device_read(struct file *flip, char __user *user_buf, size_t count, loff_t *offset) {
    ssize_t bytes_read;

    pr_info(DEVICE_NAME ": device_read: count=%zu, offset=%lld, buffer_len=%zu\n", count, *offset, buffer_len);

    if (wait_event_interruptible(read_queue, buffer_len > 0)) {
        pr_info(DEVICE_NAME ": device_read: interrupted\n");
        return -ERESTARTSYS;
    }

    mutex_lock(&buffer_mutex);

    if (count > buffer_len)
        count = buffer_len;

    if (copy_to_user(user_buf, device_buffer, count)) {
        mutex_unlock(&buffer_mutex);
        return -EFAULT;
    }

    memmove(device_buffer, device_buffer + count, buffer_len - count);
    buffer_len -= count;

    bytes_read = count;
    pr_info(DEVICE_NAME ": device_read: successfully read %zd bytes\n", bytes_read);

    mutex_unlock(&buffer_mutex);

    return bytes_read;
}

static ssize_t device_write(struct file *flip, const char __user *user_buf, size_t count, loff_t *offset) {
    ssize_t bytes_written;

    pr_info(DEVICE_NAME ": device_write: count=%zu, offset=%lld, buffer_len=%zu\n", count, *offset, buffer_len);

    if (count + buffer_len > BUFFER_SIZE)
        count = BUFFER_SIZE - buffer_len;

    mutex_lock(&buffer_mutex);

    if (copy_from_user(device_buffer + buffer_len, user_buf, count)) {
        mutex_unlock(&buffer_mutex);
        return -EFAULT;
    }

    buffer_len += count;
    bytes_written = count;

    pr_info(DEVICE_NAME ": device_write: successfully wrote %zd bytes\n", bytes_written);

    wake_up_interruptible(&read_queue);

    mutex_unlock(&buffer_mutex);

    return bytes_written;
}

static long device_ioctl(struct file *flip, unsigned int cmd, unsigned long arg) {
    int is_empty;

    pr_info(DEVICE_NAME ": device_ioctl: cmd=0x%x\n", cmd);

    switch (cmd) {
        case DRIVER_CLEAR_BUF:
            pr_info(DEVICE_NAME ": device_ioctl: DRIVER_CLEAR_BUF\n");
            mutex_lock(&buffer_mutex);
            buffer_len = 0;
            mutex_unlock(&buffer_mutex);
            break;

        case DRIVER_BUF_IS_EMPTY:
            pr_info(DEVICE_NAME ": device_ioctl: DRIVER_BUF_IS_EMPTY\n");
            mutex_lock(&buffer_mutex);
            is_empty = (buffer_len == 0) ? 1 : 0;
            mutex_unlock(&buffer_mutex);

            if (copy_to_user((int __user *)arg, &is_empty, sizeof(int)))
                return -EFAULT;
            break;

        default:
            return -ENOTTY;
    }

    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
};

static int __init device_init(void) {
    int res;

    pr_info(DEVICE_NAME ": trying to initialize the driver\n");

    res = alloc_chrdev_region(&dev_no, 0, 1, DEVICE_NAME);
    if (res < 0) {
        pr_err(DEVICE_NAME ": failed to allocate chrdev region\n");
        return res;
    }

    cdev_init(&dev, &fops);
    res = cdev_add(&dev, dev_no, 1);
    if (res < 0) {
        pr_err(DEVICE_NAME ": failed to add cdev\n");
        unregister_chrdev_region(dev_no, 1);
        return res;
    }

    dev_class = class_create(CLASS_NAME);
    if (IS_ERR(dev_class)) {
        pr_err(DEVICE_NAME ": failed to create class\n");
        cdev_del(&dev);
        unregister_chrdev_region(dev_no, 1);
        return PTR_ERR(dev_class);
    }

    device = device_create(dev_class, NULL, dev_no, NULL, DEVICE_NAME);
    if (IS_ERR(device)) {
        pr_err(DEVICE_NAME ": failed to create device\n");
        class_destroy(dev_class);
        cdev_del(&dev);
        unregister_chrdev_region(dev_no, 1);
        return PTR_ERR(device);
    }

    mutex_init(&buffer_mutex);
    init_waitqueue_head(&read_queue);

    pr_info(DEVICE_NAME ": successfully initialized the driver\n");

    return 0;
}

static void __exit device_exit(void) {
    device_destroy(dev_class, dev_no);
    class_destroy(dev_class);
    cdev_del(&dev);
    unregister_chrdev_region(dev_no, 1);
    pr_info(DEVICE_NAME ": driver unloaded\n");
}

module_init(device_init);
module_exit(device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MAI");
MODULE_DESCRIPTION("Character device driver for practice 4");
