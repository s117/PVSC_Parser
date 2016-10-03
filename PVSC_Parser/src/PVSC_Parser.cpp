//
//  Parser.cpp
//  PVSC_Parser
//
//  Created by s117 on 16/9/30.
//  Copyright © 2016年 s117. All rights reserved.
//

#include "EngineCore.h"
#include "Inst_EOFC.h"
#include "Inst_nop.h"
#include "Inst_op_55.h"
#include "Inst_op_56.h"
#include "Inst_Timestamp.h"
#include "Inst_Note.h"
#include "PVSC_Parser.h"

#define PVSC_LE             (0x43535650) //'PVSC'
#define PVSC_HEADER_LEN		(72)


STEP PVSC_Parser::parse_dsc(DSC_Info *info, const uint8_t* sequence, uint32_t len_sequence) {
    if(info == nullptr)
        return STEP_UNKNOW_INSTRUCTION;

    i55->set_info(info);
    i56->set_info(info);
    it->set_info(info);
    in->set_info(info);
    ieof->set_info(info);
    inop->set_info(info);

    STEP step;

    if(LE32((uint32_t*)sequence) == PVSC_LE) { // PVSC file(F2&X)
        if (len_sequence < PVSC_HEADER_LEN)
            return STEP_BAD_INSTRUCTION_FORMAT;

        uint32_t header_payload_1 = LE32((uint32_t*)(sequence+4));
        uint32_t header_payload_2 = LE32((uint32_t*)(sequence+20));
        uint32_t header_offset_8 = LE32((uint32_t*)(sequence+8));
        uint32_t header_version = LE32((uint32_t*)(sequence+12));
        uint32_t header_UID = LE32((uint32_t*)(sequence+32));
        uint32_t header_endian_flag_le32 = LE32((uint32_t*)(sequence+48));
        uint32_t header_endian_flag_actual = LE32((uint32_t*)(sequence+64));

        if(header_offset_8 != 0x00000040) {
            return STEP_BAD_INSTRUCTION_FORMAT;
        }

        if(header_version == 0x18000000) {
            info->ver = DSC_Info::VERSION::F2;
        } else if(header_version == 0x10000000) {
            info->ver = DSC_Info::VERSION::X;
        } else {
            return STEP_BAD_INSTRUCTION_FORMAT;
        }

        //if((header_payload_1 != header_payload_2) || (header_payload_1+112 != len_sequence)) {
        if(header_payload_1 != header_payload_2) {
            return STEP_BAD_INSTRUCTION_FORMAT;
        }

        if(header_endian_flag_le32 == header_endian_flag_actual) {
            core->set_endian(ENDIAN_TYPE::ENDIAN_LE);
            info->endian = ENDIAN_TYPE::ENDIAN_LE;
        } else if (header_endian_flag_le32 ==
                   ENDIAN_REVERSE_32(header_endian_flag_actual)) {
            core->set_endian(ENDIAN_TYPE::ENDIAN_BE);
            info->endian = ENDIAN_TYPE::ENDIAN_BE;
        } else {
            return STEP_BAD_INSTRUCTION_FORMAT;
        }
#ifdef DEBUG
        printf("#PVSC\n");
#endif
        core->set_sequence(sequence+PVSC_HEADER_LEN, len_sequence-PVSC_HEADER_LEN);

        while (1) {
            step = core->step();
            if (step & (1 << 31)) {
                if(step == STEP_END_OF_SEQUENCE)
                    break;
                printf("fatal error, code: %08X", step);
                break;
            }
        }
    }

    return step;
}

void PVSC_Parser::free_info(DSC_Info *info) {
    std::list<TimeStamp*>::iterator it_ts;
    std::list<Inst*>::iterator it_inst;
    it_ts = info->event_seq.begin();
    while(it_ts != info->event_seq.end()) {
        for(it_inst = (*it_ts)->inst_list.begin(); it_inst != (*it_ts)->inst_list.end(); ++it_inst) {
            switch ((*it_inst)->itype) {
            case Inst::InstType::NOTE:
                delete ((Note*)(*it_inst)->idata);
                break;
            case Inst::InstType::I55:
                delete ((I55*)(*it_inst)->idata);
                break;
            case Inst::InstType::I56:
                delete ((I56*)(*it_inst)->idata);
                break;
            }
            delete *it_inst;
        }
        delete *it_ts;
        it_ts = info->event_seq.erase(it_ts);
    }
}

PVSC_Parser::PVSC_Parser() {
    core = new EngineCore();
    i55 = new Inst_op_55();
    i56 = new Inst_op_56();
    it = new Inst_Timestamp();
    in = new Inst_Note();
    ieof = new Inst_EOFC();
    inop = new Inst_nop();

    core->add_inst(i55);
    core->add_inst(i56);
    core->add_inst(it);
    core->add_inst(in);
    core->add_inst(ieof);
    core->add_inst(inop);
}

PVSC_Parser::~PVSC_Parser() {
    delete core;
    delete i55;
    delete i56;
    delete it;
    delete in;
    delete ieof;
    delete inop;
}

