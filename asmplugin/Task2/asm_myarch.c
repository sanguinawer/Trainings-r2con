#include <stdio.h>
#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_asm.h>
static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	ut32 *dw;
	int size = 1;
	char mybuf[sizeof (op->buf_asm)];
	switch(*buf) {
		case 0:
			dw = &buf[1];
			snprintf(mybuf, sizeof (mybuf), "LDR stk , 0x%08x",*dw);
			strcpy(op->buf_asm, mybuf);
			size = 5;
			break;
		case 1:
			strcpy(op->buf_asm,"LDR r1 , stk");
			size = 1;
			break;
		case 2:
			strcpy(op->buf_asm,"LDR r2 , stk");
			size = 1;
			break;
		case 3:
			strcpy(op->buf_asm,"ADD stk , r1 , r2");
			size = 1;
			break;
		case 4:
			strcpy(op->buf_asm,"SUB stk , r1 , r2");
			size = 1;
			break;
		default:
			strcpy(op->buf_asm, "nop");
			break;
	}
	op->size = size;
	return size;
}
static int assemble(RAsm *a, RAsmOp *op, const char *buf) {
	return 0;
}
RAsmPlugin r_asm_plugin_myarch= {
        .name = "myarch",
        .arch = "myarch",
        .license = "LGPL3",
        .bits = 32,
        .endian = R_SYS_ENDIAN_NONE,
        .desc = "my asm skeleton",
        .disassemble = &disassemble,
        .assemble = &assemble
};

#ifndef CORELIB
struct r_lib_struct_t radare_plugin = {
        .type = R_LIB_TYPE_ASM,
        .data = &r_asm_plugin_myarch,
        .version = R2_VERSION
};
#endif
