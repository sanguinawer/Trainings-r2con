#include <string.h>
#include <r_types.h>
#include <r_lib.h>
#include <r_asm.h>
#include <r_anal.h>

static int myanal_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len) {
	if (op == NULL)
		return 1;
	memset (op, 0, sizeof (RAnalOp));
	op->type = R_ANAL_OP_TYPE_NULL;
	op->delay = 0;
	op->jump = op->fail = -1;
	op->ptr = op->val = -1;
	op->addr = addr;
	op->refptr = 0;
	op->size = 0;
	r_strbuf_setf (&op->esil, "nop");
	op->size = 1;
	return op->size;
}

static char *get_reg_profile(RAnal *anal) {
	return strdup (
		"=PC	pc\n"
		"=A0	r1\n"
		"=A1	r2\n"
		"gpr	pc	.32	0	0\n" // program counter
		"gpr	stk	.32	4	0\n" // temp reg
		"gpr	r1	.32	8	0\n" // reg1
		"gpr	r2	.32	12	0\n" // reg2
	);
}

static int set_reg_profile(RAnal *anal) {
	const char *p = \
		"=PC	pc\n"
		"=A0	r1\n"
		"=A1	r2\n"
		"gpr	pc	.32	0	0\n"  // program counter
		"gpr	stk	.32	4	0\n"  // temp reg
		"gpr	r1	.32	8	0\n"  // reg1
		"gpr	r2	.32	12	0\n"; // reg2
	return r_reg_set_profile_string (anal->reg, p);
}

struct r_anal_plugin_t r_anal_plugin_myarch = {
	.name = "myarch",
	.desc = "myarch code analysis plugin",
	.license = "LGPL3",
	.arch = "myarch",
	.bits = 32,
	.esil = true,
	.op = &myanal_op,
	.get_reg_profile = get_reg_profile,
	.set_reg_profile = set_reg_profile,
};

#ifndef CORELIB
struct r_lib_struct_t radare_plugin = {
	.type = R_LIB_TYPE_ANAL,
	.data = &r_anal_plugin_myarch,
	.version = R2_VERSION
};
#endif
