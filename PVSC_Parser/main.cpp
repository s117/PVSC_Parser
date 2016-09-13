#include <stdio.h>
#include <stdlib.h>
#include "EngineCore.h"

#include "Inst_PVSC_Header.h"
#include "Inst_EOFC.h"
#include "Inst_nop.h"
#include "Inst_op_55.h"
#include "Inst_op_56.h"
#include "Inst_Timestamp.h"
#include "Inst_Note.h"

#include "712_extreme.h"

/*
int main(int argc, char* argv[]) {
	STEP step = 0;
	DSC_Info info;
    info.endian = ENDIAN_LE;
    info.ver = DSC_Info::VERSION::X;
	Inst_op_55 *i55 = new Inst_op_55(&info);
	Inst_op_56 *i56 = new Inst_op_56(&info);
	Inst_Timestamp *it = new Inst_Timestamp(&info);
	Inst_Note *in = new Inst_Note(&info);
    Inst_EOFC *ieof = new Inst_EOFC(&info);
    Inst_nop *inop = new Inst_nop(&info);
    Inst_PVSC_Header *iphdr = new Inst_PVSC_Header(&info);
	EngineCore	*core = new EngineCore();
	core->add_inst(i55);
	core->add_inst(i56);
	core->add_inst(it);
	core->add_inst(in);
    core->add_inst(ieof);
    core->add_inst(inop);
    core->add_inst(iphdr);
	core->set_sequence(data, sizeof(data));
	while (1) {
		step = core->step();
		if (step & (1 << 31)) {
            if(step == STEP_END_OF_SEQUENCE)
                break;
			printf("fatal error, code: %08X", step);
			exit(1);
		}
	}
	return 0;
    
}
*/

#define PVSC_LE             (0x43535650) //'PVSC'
#define PVSC_HEADER_LEN		(72)


STEP parse_dsc(const uint8_t* sequence, uint32_t len_sequence){
    STEP step;
    DSC_Info info;
    EngineCore* core = new EngineCore();
    Inst_op_55 *i55 = new Inst_op_55(&info);
    Inst_op_56 *i56 = new Inst_op_56(&info);
    Inst_Timestamp *it = new Inst_Timestamp(&info);
    Inst_Note *in = new Inst_Note(&info);
    Inst_EOFC *ieof = new Inst_EOFC(&info);
    Inst_nop *inop = new Inst_nop(&info);
    
    if(LE32((uint32_t*)sequence) == PVSC_LE){ // PVSC file(F2&X)
        if (len_sequence < PVSC_HEADER_LEN)
            return STEP_BAD_INSTRUCTION_FORMAT;
        
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
            info.ver = DSC_Info::VERSION::F2;
        } else if(header_version == 0x10000000){
            info.ver = DSC_Info::VERSION::X;
        } else{
            return STEP_BAD_INSTRUCTION_FORMAT;
        }
        
        if((header_payload_1 != header_payload_2) || (header_payload_1+112 != len_sequence)){
            return STEP_BAD_INSTRUCTION_FORMAT;
        }
        
        if(header_endian_flag_le32 == header_endian_flag_actual){
            core->set_endian(ENDIAN_TYPE::ENDIAN_LE);
            info.endian = ENDIAN_TYPE::ENDIAN_LE;
        } else if (header_endian_flag_le32 ==
                   ENDIAN_REVERSE_32(header_endian_flag_actual)){
            core->set_endian(ENDIAN_TYPE::ENDIAN_BE);
            info.endian = ENDIAN_TYPE::ENDIAN_BE;
        } else {
            return STEP_BAD_INSTRUCTION_FORMAT;
        }
        
        printf("#PVSC\n");
        
        core->add_inst(i55);
        core->add_inst(i56);
        core->add_inst(it);
        core->add_inst(in);
        core->add_inst(ieof);
        core->add_inst(inop);
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
    
    delete core;
    delete i55;
    delete i56;
    delete it;
    delete in;
    delete ieof;
    delete inop;
    
    return step;
}

int main(int argc, char* argv[]){
    parse_dsc(data, sizeof(data));
}
