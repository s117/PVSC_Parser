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
            printf("Off:%08X, Note %s_DOWN, time: %d(%d + %d), hold param: %d(length), %d. ",
                   core->get_offset() + len_header,
                   ((note->note_keycode <= 0x1c) ? NoteName[note->note_keycode] : "OUT_OF_RANGE"),
                   note->note_time_offset + stamp->time,
                   stamp->time,
                   note->note_time_offset,
                   note->note_hold_length,
                   note->note_hold2);
        } else {
            printf("Off:%08X, Note %s_UP, time: %d(%d + %d). ",
                   core->get_offset() + 72,
                   ((note->note_keycode <= 0x1c) ? NoteName[note->note_keycode] : "OUT_OF_RANGE"),
                   note->note_time_offset + stamp->time,
                   stamp->time,
                   note->note_time_offset);
        }
    } else if((NOTE_KEYCODE::TRIANGLE_RUSH <= note->note_keycode) && (note->note_keycode <= NOTE_KEYCODE::SQUARE_RUSH)) {
        printf("Off:%08X, Note %s, time: %d(%d + %d), rush param: %d(length), %d. ",
               core->get_offset() + len_header,
               ((note->note_keycode <= 0x1c) ? NoteName[note->note_keycode] : "OUT_OF_RANGE"),
               note->note_time_offset + stamp->time,
               stamp->time,
               note->note_time_offset,
               note->note_hold_length,
               note->note_hold2);
    } else {
        printf("Off:%08X, Note %s, time: %d(%d + %d). ",
               core->get_offset() + len_header,
               ((note->note_keycode <= 0x1c) ? NoteName[note->note_keycode] : "OUT_OF_RANGE"),
               note->note_time_offset + stamp->time,
               stamp->time,
               note->note_time_offset);
    }
    printf("f_off = %d, ", note->file_offset);
    printf("key = %d, ", note->note_keycode);
    printf("h_len = %d, ", note->note_hold_length);
    printf("h2 = %d, ", note->note_hold2);
    printf("co_X = %d, ", note->note_cord_X);
    printf("co_Y = %d, ", note->note_cord_Y);
    printf("cur_1 = %d, ", note->note_curve_rel1);
    printf("cur_2 = %d, ", note->note_curve_rel2);
    printf("tm_off = %d, ", note->note_time_offset);
    printf("unk1 = %d, ", note->note_unk1);
    printf("unk2 = %d, ", note->note_unk2);
    printf("unk3 = %d, ", note->note_unk3);
    printf("unk4 = %d \n", note->note_unk4);

#endif

    return INST_SIZE;
}

Inst_Note::Inst_Note(): DSC_Inst(INST_OP_CODE, INST_SIZE) {}

Inst_Note::Inst_Note(DSC_Info* info) : DSC_Inst(INST_OP_CODE, INST_SIZE, info) {}

Inst_Note::~Inst_Note() {}
