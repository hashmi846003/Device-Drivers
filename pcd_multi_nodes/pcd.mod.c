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
	{ 0x4c26a36c, "class_destroy" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xfb8e9076, "class_create" },
	{ 0x0e3db14b, "cdev_init" },
	{ 0x7be40665, "cdev_add" },
	{ 0x72bc2e84, "device_create" },
	{ 0x546c19d9, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0x092a35a2, "_copy_to_user" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xdf5538eb, "device_destroy" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0xf507125d, "cdev_del" },
	{ 0x3583050f, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x4c26a36c,
	0x0bc5fb0d,
	0x9f222e1e,
	0xfb8e9076,
	0x0e3db14b,
	0x7be40665,
	0x72bc2e84,
	0x546c19d9,
	0xa61fd7aa,
	0x092a35a2,
	0x092a35a2,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0xdf5538eb,
	0x90a48d82,
	0xf507125d,
	0x3583050f,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"class_destroy\0"
	"unregister_chrdev_region\0"
	"alloc_chrdev_region\0"
	"class_create\0"
	"cdev_init\0"
	"cdev_add\0"
	"device_create\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"_copy_to_user\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"device_destroy\0"
	"__ubsan_handle_out_of_bounds\0"
	"cdev_del\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "8DBB791ED1B3B4D793A666A");
