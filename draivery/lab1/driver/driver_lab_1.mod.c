#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x92997ed8, "_printk" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0xcccfd495, "cdev_add" },
	{ 0xc488c3b0, "device_create" },
	{ 0x70d6ed6d, "class_create" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xbb43d076, "device_destroy" },
	{ 0xb43f9365, "ktime_get" },
	{ 0xbadf77d8, "cdev_init" },
	{ 0x1844a757, "cdev_del" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x6bc45351, "class_destroy" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xa1a94982, "module_layout" },
};

MODULE_INFO(depends, "");

