#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kruglyankin from 307");
MODULE_DESCRIPTION("Simple kernel module for practice 2");
MODULE_VERSION("1.0");

static int __init hello_init(void) {
    pr_info("Hello from the mai\n");
    return 0;
}

static void __exit hello_exit(void) {
    pr_info("Goodbye from the mai\n");
}

module_init(hello_init);
module_exit(hello_exit);
