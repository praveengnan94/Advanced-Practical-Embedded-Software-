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
	{ 0x55e1780b, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x78bcdc29, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x263e6ebd, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x33fcf44a, __VMLINUX_SYMBOL_STR(__kfifo_out_r) },
	{ 0x9829fc11, __VMLINUX_SYMBOL_STR(__kfifo_out_peek_r) },
	{ 0xce4e47b6, __VMLINUX_SYMBOL_STR(__kfifo_skip_r) },
	{ 0x7846af3e, __VMLINUX_SYMBOL_STR(__kfifo_len_r) },
	{ 0x3955fcf6, __VMLINUX_SYMBOL_STR(__kfifo_in_r) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2484adc3, __VMLINUX_SYMBOL_STR(__kfifo_to_user_r) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x27cfea5a, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfeebc7c4, __VMLINUX_SYMBOL_STR(__kfifo_from_user_r) },
	{ 0x615b2fa, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "2082DD560C22F049432B5FE");
