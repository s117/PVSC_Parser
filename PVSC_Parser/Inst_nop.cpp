#include "Inst_nop.h"
#include <assert.h>

#define INST_OP_CODE	(0x00000000)
#define INST_SIZE		(4)


STEP Inst_nop::parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) {
    if (len_sequence < INST_SIZE)
        return STEP_BAD_INSTRUCTION_FORMAT;

    assert(info != nullptr);
    assert(LE32((uint32_t*)sequence) == this->opcode);

    return INST_SIZE;
}

Inst_nop::Inst_nop() : DSC_Inst(INST_OP_CODE, INST_SIZE) {}

Inst_nop::Inst_nop(DSC_Info *info) : DSC_Inst(INST_OP_CODE, INST_SIZE, info) {}

Inst_nop::~Inst_nop() {}
