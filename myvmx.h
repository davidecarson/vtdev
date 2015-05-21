/*
 *    myvmx.h
 */

typedef struct {
        unsigned int    eip;
        unsigned int    eflags;
        unsigned int    eax;
        unsigned int    ecx;
        unsigned int    edx;
        unsigned int    ebx;
        unsigned int    esp;
        unsigned int    ebp;
        unsigned int    esi;
        unsigned int    edi;
        unsigned int     es;
        unsigned int     cs;
        unsigned int     ss;
        unsigned int     ds;
        unsigned int     fs;
        unsigned int     gs;
        } regs_ia32;


