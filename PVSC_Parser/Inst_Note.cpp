#include "Inst_Note.h"
#include <assert.h>

#define INST_OP_CODE	(0x00000006)
#define INST_SIZE		(52)
/*
TRI 8
CIRC 9
CROSS A
RECT B
CIRC R 1A
CROSS R 1B
*/
const char* const NoteName[] = {
	"TRIG",
	"CIRC",
	"CROS",
	"SQUR",
	"UP  ",
	"RGHT",
	"DOWN",
	"LEFT",
	"TRIG_LONG",
	"CIRC_LONG",
	"CROS_LONG",
	"SQUR_LONG",
	"STAR",
    "UNK_D",
    "DOUBLE_STAR",
    "CHANCE_STAR",
    "UNK_10",
    "UNK_11",
    "UNK_12",
    "UNK_13",
    "UNK_14",
    "UNK_15",
    "STAR_LINE_START",
    "STAR_LINE_END  ",
    "UNK_18",
    "TRIG_RUSH",
    "CIRC_RUSH",
    "CROS_RUSH",
    "SQUR_RUSH",
};
enum NOTE_KEYCODE {
	TRIANGLE = 0,
	CIRCLE = 1,
	CROSS = 2,
	SQUARE = 3,
    UP = 4,
    RIGHT = 5,
    DOWN = 6,
    LEFT = 7,
    TRIANGLE_LONG = 8,
    CIRCLE_LONG = 9,
    CROSS_LONG = 0xA,
    SQUARE_LONG = 0xB,
    STAR = 0xC,
    DOUBLE_STAR = 0xE,
    CHANCE_STAR = 0xF,
    STAR_LINE_START = 0x16,
    STAR_LINE_END = 0x17,
    TRIANGLE_RUSH = 0x19,
    CIRCLE_RUSH = 0x1A,
    CROSS_RUSH = 0x1B,
    SQUARE_RUSH = 0x1C,
};

bool Inst_Note::register_inst(IN EngineCore* engine, OUT uint32_t* opcode) {
	if (core == nullptr) {
		core = engine;
        *opcode = (core->get_endian() == ENDIAN_LE)?INST_OP_CODE:ENDIAN_REVERSE_32(INST_OP_CODE);
        this->opcode = *opcode;
		return true;
	}
	return false;
}

bool Inst_Note::unregister_inst(IN EngineCore* engine) {
	if (core == engine) {
		core = nullptr;
		return true;
	}
	return false;
}

//#define LE32(addr) (*(uint32_t*)(addr))

STEP Inst_Note::parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) {
	if (len_sequence < INST_SIZE)
		return STEP_BAD_INSTRUCTION_FORMAT;

	assert(*((uint32_t*)sequence) == this->opcode);
    
	uint32_t note_keycode = DATA32(info->endian,(uint32_t*)(sequence + 0x4));

	uint32_t note_hold_length = DATA32(info->endian,(uint32_t*)(sequence + 0x8));
	uint32_t note_hold2 = DATA32(info->endian,(uint32_t*)(sequence + 0xC));

	uint32_t note_cord_X = DATA32(info->endian,(uint32_t*)(sequence + 0x10));
	uint32_t note_cord_Y = DATA32(info->endian,(uint32_t*)(sequence + 0x14));
    
	uint32_t note_curve_rel1 = DATA32(info->endian,(uint32_t*)(sequence + 0x18));
	uint32_t note_curve_rel2 = DATA32(info->endian,(uint32_t*)(sequence + 0x1C));

	uint32_t note_time_offset = DATA32(info->endian,(uint32_t*)(sequence + 0x20));
	uint32_t note_unk1 = DATA32(info->endian,(uint32_t*)(sequence + 0x24));
	uint32_t note_unk2 = DATA32(info->endian,(uint32_t*)(sequence + 0x28));
	uint32_t note_unk3 = DATA32(info->endian,(uint32_t*)(sequence + 0x2C));
	uint32_t note_unk4 = DATA32(info->endian,(uint32_t*)(sequence + 0x30));
    
    if((NOTE_KEYCODE::TRIANGLE_HOLD <= note_keycode) && (note_keycode <= NOTE_KEYCODE::RECTANGLE_HOLD)){
        if(note_hold_length != 0xffffffff){
            printf("Off:%08X, Note %s_DOWN, time: %d(%d + %d), hold param: %d(length), %d\n", core->get_offset() + 72, ((note_keycode <= 0x1c) ? NoteName[note_keycode] : "OUT_OF_RANGE"), note_time_offset + this->info->base_time, this->info->base_time, note_time_offset, note_hold_length, note_hold2);
        }else{
            printf("Off:%08X, Note %s_UP, time: %d(%d + %d)\n", core->get_offset() + 72, ((note_keycode <= 0x1c) ? NoteName[note_keycode] : "OUT_OF_RANGE"), note_time_offset + this->info->base_time, this->info->base_time, note_time_offset);
        }
    }else if((NOTE_KEYCODE::TRIANGLE_RUSH <= note_keycode) && (note_keycode <= NOTE_KEYCODE::RECTANGLE_RUSH)){
        printf("Off:%08X, Note %s, time: %d(%d + %d), rush param: %d(length), %d\n", core->get_offset() + 72, ((note_keycode <= 0x1c) ? NoteName[note_keycode] : "OUT_OF_RANGE"), note_time_offset + this->info->base_time, this->info->base_time, note_time_offset, note_hold_length, note_hold2);
    }else{
        
        printf("Off:%08X, Note %s, time: %d(%d + %d)\n", core->get_offset() + 72, ((note_keycode <= 0x1c) ? NoteName[note_keycode] : "OUT_OF_RANGE"), note_time_offset + this->info->base_time, this->info->base_time, note_time_offset);
    }
    

	return INST_SIZE;
}

Inst_Note::Inst_Note(DSC_Info* info) {
	this->info = info;
}


Inst_Note::~Inst_Note() {}
