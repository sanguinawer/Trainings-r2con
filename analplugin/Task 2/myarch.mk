OBJ_MYARCH=anal_myarch.o

STATIC_OBJ+=${OBJ_MYARCH}
TARGET_MYARCH=anal_myarch.${EXT_SO}

ALL_TARGETS+=${TARGET_MYARCH}

${TARGET_MYARCH}: ${OBJ_MYARCH}
	${CC} $(call libname,anal_myarch) ${LDFLAGS} ${CFLAGS} -o anal_myarch.${EXT_SO} ${OBJ_MYARCH}
