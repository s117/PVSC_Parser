//
//  Inst_DSC.cpp
//  PVSC_Parser
//
//  Created by s117 on 16/9/30.
//  Copyright © 2016年 s117. All rights reserved.
//

#include "DSC_Inst.h"

#include "Inst_nop.h"
#include <assert.h>

bool DSC_Inst::register_inst(IN EngineCore* engine, OUT uint32_t* opcode) {
    if (core == nullptr) {
        core = engine;
        //*opcode = this->opcode;
        *opcode = (core->get_endian() == ENDIAN_LE)?this->opcode:ENDIAN_REVERSE_32(this->opcode);
        return true;
    }
    return false;
}

bool DSC_Inst::unregister_inst(IN EngineCore* engine) {
    if (core == engine) {
        core = nullptr;
        return true;
    }
    return false;
}

STEP DSC_Inst::parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) {
    if (len_sequence < this->size)
        return STEP_BAD_INSTRUCTION_FORMAT;

    assert(info != nullptr);
    assert(LE32((uint32_t*)sequence) == this->opcode);
    // nop
    return this->size;
}


void DSC_Inst::set_info(DSC_Info* info) {
    this->info = info;
}

DSC_Info* DSC_Inst::get_info() {
    return this->info;
}


DSC_Inst::DSC_Inst(uint32_t OPCODE, uint32_t SIZE) {
    this->opcode = OPCODE;
    this->size = SIZE;
}

DSC_Inst::DSC_Inst(uint32_t OPCODE, uint32_t SIZE, DSC_Info* info) {
    this->opcode = OPCODE;
    this->size = SIZE;
    this->info = info;
}

DSC_Inst::~DSC_Inst() {}

