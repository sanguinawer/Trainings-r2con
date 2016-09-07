#include <stdio.h>
#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_asm.h>
static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	return 0;
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
