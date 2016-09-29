#ifndef __H_GLOBAL_DEF
#define __H_GLOBAL_DEF

#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

#include "EndianUtils.h"

typedef uint32_t ERR_CODE;
#define CODE_OK						0
#define CODE_ERR_INVALID_ARGS		(1<<0)

typedef int32_t STEP;
#define STEP_UNKNOW_INSTRUCTION		((1<<31)|(1<<0))
#define STEP_TOO_SHORT				((1<<31)|(1<<1))
#define STEP_BAD_INSTRUCTION_FORMAT	((1<<31)|(1<<2))
#define STEP_BUFFER_OVERFLOW		((1<<31)|(1<<3))
#define STEP_END_OF_SEQUENCE		((1<<31)|(1<<4))
#define STEP_SEQUENCE_UNSET			((1<<31)|(1<<5))

#define IN
#define OUT

#endif
