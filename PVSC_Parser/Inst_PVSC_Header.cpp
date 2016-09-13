#include "Inst_PVSC_Header.h"
#include <assert.h>

#define INST_OP_CODE	(0x43535650) //'PVSC'
#define INST_SIZE		(72)

bool Inst_PVSC_Header::register_inst(IN EngineCore* engine, OUT uint32_t* opcode) {
    if (core == nullptr) {
        core = engine;
        *opcode = INST_OP_CODE;
        return true;
    }
    return false;
}

bool Inst_PVSC_Header::unregister_inst(IN EngineCore* engine) {
    if (core == engine) {
        core = nullptr;
        return true;
    }
    return false;
}

#define INST_OP_CODE	(0x43535650) //'PVSC'
#define INST_SIZE		(72)
STEP Inst_PVSC_Header::parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) {
    if (len_sequence < INST_SIZE)
        return STEP_BAD_INSTRUCTION_FORMAT;
    
    assert(DATA32(core->get_endian(),(uint32_t*)sequence) == INST_OP_CODE);
    
    uint32_t header_payload_1 = LE32((uint32_t*)(sequence+4));
    uint32_t header_payload_2 = LE32((uint32_t*)(sequence+20));
    uint32_t header_offset_8 = LE32((uint32_t*)(sequence+8));
    uint32_t header_version = LE32((uint32_t*)(sequence+12));
    uint32_t header_UID = LE32((uint32_t*)(sequence+32));
    uint32_t header_endian_flag_le32 = LE32((uint32_t*)(sequence+48));
    uint32_t header_endian_flag_actual = LE32((uint32_t*)(sequence+64));
    
    if(header_offset_8 != 0x00000040){
        return STEP_BAD_INSTRUCTION_FORMAT;
    }
        
    if(header_version == 0x18000000){
        this->info->ver = DSC_Info::VERSION::F2;
    } else if(header_version == 0x10000000){
        this->info->ver = DSC_Info::VERSION::X;
    } else{
        return STEP_BAD_INSTRUCTION_FORMAT;
    }
    
    if((header_payload_1 != header_payload_2) || (header_payload_1+112 != len_sequence)){
        return STEP_BAD_INSTRUCTION_FORMAT;
    }
    
    if(header_endian_flag_le32 == header_endian_flag_actual){
        core->set_endian(ENDIAN_TYPE::ENDIAN_LE);
        this->info->endian = ENDIAN_TYPE::ENDIAN_LE;
    } else if (header_endian_flag_le32 ==
               ENDIAN_REVERSE_32(header_endian_flag_actual)){
        core->set_endian(ENDIAN_TYPE::ENDIAN_BE); // TODO
        this->info->endian = ENDIAN_TYPE::ENDIAN_BE;
    } else {
        return STEP_BAD_INSTRUCTION_FORMAT;
    }
    
    printf("#PVSC\n");
    
    return INST_SIZE;
}

Inst_PVSC_Header::Inst_PVSC_Header(DSC_Info *info) {
    this->info = info;
}


Inst_PVSC_Header::~Inst_PVSC_Header() {}