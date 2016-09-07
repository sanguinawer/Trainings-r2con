OBJ_MYARCH=asm_myarch.o

TARGET_MYARCH=asm_myarch.${EXT_SO}
STATIC_OBJ+=${OBJ_MYARCH}

ifeq ($(WITHPIC),1)
ALL_TARGETS+=${TARGET_MYARCH}
${TARGET_MYARCH}: ${OBJ_MYARCH}
	${CC} $(call libname,asm_myarch) ${LDFLAGS} ${CFLAGS} -o ${TARGET_MYARCH} ${OBJ_MYARCH}
endif
