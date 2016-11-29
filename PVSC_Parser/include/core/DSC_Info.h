#ifndef __H_DSC_INFO
#define __H_DSC_INFO

#include "GlobalDef.h"
#include <list>

#ifndef __C_DSC_INFO
extern const char* const NoteName[];
#endif

enum NOTE_KEYCODE {
    TRIANGLE        = 0,
    CIRCLE          = 1,
    CROSS           = 2,
    SQUARE          = 3,
    UP              = 4,
    RIGHT           = 5,
    DOWN            = 6,
    LEFT            = 7,
    TRIANGLE_LONG   = 8,
    CIRCLE_LONG     = 9,
    CROSS_LONG      = 0xA,
    SQUARE_LONG     = 0xB,
    STAR            = 0xC,
    STAR_DOUBLE     = 0xE,
    STAR_CHANCE     = 0xF,
    STAR_LINE_START = 0x16,
    STAR_LINE_END   = 0x17,
    TRIANGLE_RUSH   = 0x19,
    CIRCLE_RUSH     = 0x1A,
    CROSS_RUSH      = 0x1B,
    SQUARE_RUSH     = 0x1C,
};


typedef struct __Inst {
    enum InstType {
        NOTE = 0,
        I55,
        I56
    } itype;
    void* idata;
} Inst;

typedef struct __Note {
    uint32_t note_keycode;
    uint32_t note_hold_length;
    uint32_t note_hold2;
    uint32_t note_cord_X;
    uint32_t note_cord_Y;
    uint32_t note_curve_rel1;
    uint32_t note_curve_rel2;
    uint32_t note_time_offset;
    uint32_t note_unk1;
    uint32_t note_unk2;
    uint32_t note_unk3;
    uint32_t note_unk4;

    uint32_t file_offset;
    uint32_t reverse;
} Note;

typedef struct __I55 {
    uint32_t i55_unk1;
    uint32_t file_offset;
} I55;

typedef struct __I56 {
    uint32_t i56_unk1;
    uint32_t file_offset;
} I56;

typedef struct __TimeStamp {
    uint32_t time;
    std::list<Inst*> inst_list;
} TimeStamp;

class DSC_Info {
public:
    enum VERSION {
        F,
        F2,
        X
    } ver;
    ENDIAN_TYPE endian;
    uint32_t payload_len;

    std::list<TimeStamp*> event_seq;
    ~DSC_Info();
};

#endif
