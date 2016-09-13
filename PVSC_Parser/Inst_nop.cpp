#include "Inst_nop.h"
#include <assert.h>

#define INST_OP_CODE	(0x00000000)
#define INST_SIZE		(4)

bool Inst_nop::register_inst(IN EngineCore* engine, OUT uint32_t* opcode) {
    if (core == nullptr) {
        core = engine;
        *opcode = INST_OP_CODE;
        this->opcode = *opcode;
        return true;
    }
    return false;
}

bool Inst_nop::unregister_inst(IN EngineCore* engine) {
    if (core == engine) {
        core = nullptr;
        return true;
    }
    return false;
}

STEP Inst_nop::parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) {
    if (len_sequence < INST_SIZE)
        return STEP_BAD_INSTRUCTION_FORMAT;

    assert(*((uint32_t*)sequence) == this->opcode);

    return INST_SIZE;
}

Inst_nop::Inst_nop(DSC_Info *info) {
    this->info = info;
}

Inst_nop::~Inst_nop() {}
