#include "Inst_Timestamp.h"


#include <assert.h>

#define INST_OP_CODE	(0x00000001)
#define INST_SIZE		(8)

STEP Inst_Timestamp::parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) {
    if (len_sequence < INST_SIZE)
        return STEP_BAD_INSTRUCTION_FORMAT;

    assert(LE32((uint32_t*)sequence) == this->opcode);

    TimeStamp *stamp = new TimeStamp;
    stamp->time = DATA32(info->endian,(uint32_t*)(sequence+4));
    info->event_seq.push_back(stamp);

    return INST_SIZE;
}

Inst_Timestamp::Inst_Timestamp(): DSC_Inst(INST_OP_CODE, INST_SIZE) {}

Inst_Timestamp::Inst_Timestamp(DSC_Info* info): DSC_Inst(INST_OP_CODE, INST_SIZE, info) {}

Inst_Timestamp::~Inst_Timestamp() {}
