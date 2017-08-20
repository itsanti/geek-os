#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aleksandr Kurov");

int init_module(void) {
	printk(KERN_ALERT "Hello from simplemod!\n");
	return 0;
}

void cleanup_module(void) {
	printk(KERN_ALERT "simplemod removed\n");
}
