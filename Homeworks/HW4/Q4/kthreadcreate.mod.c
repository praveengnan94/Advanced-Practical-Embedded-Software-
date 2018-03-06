#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x3d6976bf, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x651b1d9e, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x5d802f6e, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xca2e829b, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x33fcf44a, __VMLINUX_SYMBOL_STR(__kfifo_out_r) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x3955fcf6, __VMLINUX_SYMBOL_STR(__kfifo_in_r) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x65c544a3, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "777923FD918FEB8E8FD06C9");
