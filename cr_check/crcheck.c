/* 
 * 	crcheck.c
 *
 *	This program shows how to display the initial contents of 
 *	the processor's cr0 register as a 32-bit binary value.
 *
 *	cr0 access requires privilege level 0, so this creates a 
 *	kernel module
 *
 *	programmer: David Carson
 *	written on: 17 May 2015
 *      Tested with kernel 3.13.0-39 on Ubuntu 14.04 (though it is
 *      not using anything kernel-specific)
 *
 */
#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void) {
    u32 cr0, cr2, cr3;
#ifdef __x86_64__
    __asm__ __volatile__ (
        "mov %%cr0, %%rax\n\t"
        "mov %%eax, %0\n\t"
        "mov %%cr2, %%rax\n\t"
        "mov %%eax, %1\n\t"
        "mov %%cr3, %%rax\n\t"
        "mov %%eax, %2\n\t"
    : "=m" (cr0), "=m" (cr2), "=m" (cr3)
    : /* no input */
    : "%rax"
    );
#elif defined(__i386__)
    __asm__ __volatile__ (
        "mov %%cr0, %%eax\n\t"
        "mov %%eax, %0\n\t"
        "mov %%cr2, %%eax\n\t"
        "mov %%eax, %1\n\t"
        "mov %%cr3, %%eax\n\t"
        "mov %%eax, %2\n\t"
    : "=m" (cr0), "=m" (cr2), "=m" (cr3)
    : /* no input */
    : "%eax"
    );
#endif
    printk(KERN_INFO "cr0 = 0x%8.8X\n", cr0);
    printk(KERN_INFO "cr2 = 0x%8.8X\n", cr2);
    printk(KERN_INFO "cr3 = 0x%8.8X\n", cr3);
    return 0;
}

void cleanup_module(void) {
}
