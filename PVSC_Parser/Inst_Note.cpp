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

    assert(LE32((uint32_t*)sequence) == this->opcode);
    TimeStamp *stamp = this->info->event_seq.back();
    Inst *inst = new Inst;
    Note *note = new Note;

    stamp->inst_list.push_back(inst);

    inst->itype = Inst::InstType::NOTE;
    inst->idata = note;

    const int len_header = 72;
    note->file_offset = core->get_offset() + len_header;
    note->note_keycode = DATA32(info->endian,(uint32_t*)(sequence + 0x4));
    note->note_hold_length = DATA32(info->endian,(uint32_t*)(sequence + 0x8));
    note->note_hold2 = DATA32(info->endian,(uint32_t*)(sequence + 0xC));
    note->note_cord_X = DATA32(info->endian,(uint32_t*)(sequence + 0x10));
    note->note_cord_Y = DATA32(info->endian,(uint32_t*)(sequence + 0x14));
    note->note_curve_rel1 = DATA32(info->endian,(uint32_t*)(sequence + 0x18));
    note->note_curve_rel2 = DATA32(info->endian,(uint32_t*)(sequence + 0x1C));
    note->note_time_offset = DATA32(info->endian,(uint32_t*)(sequence + 0x20));
    note->note_unk1 = DATA32(info->endian,(uint32_t*)(sequence + 0x24));
    note->note_unk2 = DATA32(info->endian,(uint32_t*)(sequence + 0x28));
    note->note_unk3 = DATA32(info->endian,(uint32_t*)(sequence + 0x2C));
    note->note_unk4 = DATA32(info->endian,(uint32_t*)(sequence + 0x30));

#ifdef DEBUG
    if((NOTE_KEYCODE::TRIANGLE_LONG <= note->note_keycode) && (note->note_keycode <= NOTE_KEYCODE::SQUARE_LONG)) {
        if(note->note_hold_length != 0xffffffff) {
            printf("Off:%08X, Note %s_DOWN, time: %d(%d + %d), hold param: %d(length), %d\n",
                   core->get_offset() + len_header,
                   ((note->note_keycode <= 0x1c) ? NoteName[note->note_keycode] : "OUT_OF_RANGE"),
                   note->note_time_offset + stamp->time,
                   stamp->time,
                   note->note_time_offset,
                   note->note_hold_length,
                   note->note_hold2);
        } else {
            printf("Off:%08X, Note %s_UP, time: %d(%d + %d)\n",
                   core->get_offset() + 72,
                   ((note->note_keycode <= 0x1c) ? NoteName[note->note_keycode] : "OUT_OF_RANGE"),
                   note->note_time_offset + stamp->time,
                   stamp->time,
                   note->note_time_offset);
        }
    } else if((NOTE_KEYCODE::TRIANGLE_RUSH <= note->note_keycode) && (note->note_keycode <= NOTE_KEYCODE::SQUARE_RUSH)) {
        printf("Off:%08X, Note %s, time: %d(%d + %d), rush param: %d(length), %d\n",
               core->get_offset() + len_header,
               ((note->note_keycode <= 0x1c) ? NoteName[note->note_keycode] : "OUT_OF_RANGE"),
               note->note_time_offset + stamp->time,
               stamp->time,
               note->note_time_offset,
               note->note_hold_length,
               note->note_hold2);
    } else {
        printf("Off:%08X, Note %s, time: %d(%d + %d)\n",
               core->get_offset() + len_header,
               ((note->note_keycode <= 0x1c) ? NoteName[note->note_keycode] : "OUT_OF_RANGE"),
               note->note_time_offset + stamp->time,
               stamp->time,
               note->note_time_offset);
    }
#endif

    return INST_SIZE;
}

Inst_Note::Inst_Note(DSC_Info* info) {
    this->info = info;
}


Inst_Note::~Inst_Note() {}
