#include "Inst_op_55.h"
#include <assert.h>

#define INST_OP_CODE	(0x00000055)
#define INST_SIZE		(8)

STEP Inst_op_55::parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) {
    if (len_sequence < INST_SIZE)
        return STEP_BAD_INSTRUCTION_FORMAT;

    assert(LE32((uint32_t*)sequence) == this->opcode);

    TimeStamp *stamp = this->info->event_seq.back();
    Inst *inst = new Inst;
    I55 *i55 = new I55;

    stamp->inst_list.push_back(inst);

    inst->itype = Inst::InstType::I55;
    inst->idata = i55;

    const int len_header = 72;
    i55->file_offset = core->get_offset() + len_header;
    i55->i55_unk1 = DATA32(info->endian,(uint32_t*)(sequence + 0x4));

    return INST_SIZE;
}

Inst_op_55::Inst_op_55() : DSC_Inst(INST_OP_CODE, INST_SIZE) {}

Inst_op_55::Inst_op_55(DSC_Info *info) : DSC_Inst(INST_OP_CODE, INST_SIZE, info) {}

Inst_op_55::~Inst_op_55() {}
