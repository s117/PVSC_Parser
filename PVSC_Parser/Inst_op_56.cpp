#include "Inst_op_56.h"
#include <assert.h>

#define INST_OP_CODE	(0x00000056)
#define INST_SIZE		(8)


bool Inst_op_56::register_inst(IN EngineCore* engine, OUT uint32_t* opcode) {
	if (core == nullptr) {
		core = engine;
		*opcode = (core->get_endian() == ENDIAN_LE)?INST_OP_CODE:ENDIAN_REVERSE_32(INST_OP_CODE);
        this->opcode = *opcode;
		return true;
	}
	return false;
}

bool Inst_op_56::unregister_inst(IN EngineCore* engine) {
	if (core == engine) {
		core = nullptr;
		return true;
	}
	return false;
}

STEP Inst_op_56::parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) {
	if (len_sequence < INST_SIZE)
		return STEP_BAD_INSTRUCTION_FORMAT;

	assert(*((uint32_t*)sequence) == this->opcode);

	return INST_SIZE;
}

Inst_op_56::Inst_op_56(DSC_Info *info) {
    this->info = info;
}

Inst_op_56::~Inst_op_56() {}
