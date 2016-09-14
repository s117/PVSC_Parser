#include "Inst_EOFC.h"
#include <assert.h>

#define INST_OP_CODE	(0x43464f45) //'EOFC'
#define INST_SIZE		(16)

bool Inst_EOFC::register_inst(IN EngineCore* engine, OUT uint32_t* opcode) {
    if (core == nullptr) {
        core = engine;
        *opcode = INST_OP_CODE;
        this->opcode = *opcode;
        return true;
    }
    return false;
}

bool Inst_EOFC::unregister_inst(IN EngineCore* engine) {
    if (core == engine) {
        core = nullptr;
        return true;
    }
    return false;
}

STEP Inst_EOFC::parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) {
    if (len_sequence < INST_SIZE)
        return STEP_BAD_INSTRUCTION_FORMAT;

    assert(LE32((uint32_t*)sequence) == this->opcode);

    if(!(
                ( (*(uint32_t*)(sequence+4)) == 0x00000000)
                && ((*(uint32_t*)(sequence+8)) == 0x00000020)
                && ((*(uint32_t*)(sequence+12)) == 0x10000000)))
        return STEP_BAD_INSTRUCTION_FORMAT;

    int len_remaining = len_sequence-INST_SIZE;
    assert((len_remaining&0x3) == 0);
    len_remaining = len_remaining/4;

    for(int i = 0; i < len_remaining; ++i) {
        if(DATA32(info->endian,(uint32_t*)(sequence+INST_SIZE+4*i)) != 0x00000000)
            return STEP_BAD_INSTRUCTION_FORMAT;
    }
    printf("#EOFC\n");
    return len_sequence;
}

Inst_EOFC::Inst_EOFC(DSC_Info *info) {
    this->info = info;
}

Inst_EOFC::~Inst_EOFC() {}
