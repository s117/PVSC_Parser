//
//  Parser.hpp
//  PVSC_Parser
//
//  Created by s117 on 16/9/30.
//  Copyright © 2016年 s117. All rights reserved.
//

#ifndef __H_PARSER
#define __H_PARSER
#include "GlobalDef.h"
#include "DSC_Info.h"
#include "EngineCore.h"
#include "EngineCore.h"
#include "Inst_EOFC.h"
#include "Inst_nop.h"
#include "Inst_op_55.h"
#include "Inst_op_56.h"
#include "Inst_Timestamp.h"
#include "Inst_Note.h"

class PVSC_Parser {
public:
    PVSC_Parser();
    ~PVSC_Parser();
    STEP parse_dsc(DSC_Info *info, const uint8_t* sequence, uint32_t len_sequence);
private:
    EngineCore* core;
    Inst_op_55 *i55;
    Inst_op_56 *i56;
    Inst_Timestamp *it;
    Inst_Note *in;
    Inst_EOFC *ieof;
    Inst_nop *inop;
};
#endif /* Parser_hpp */
