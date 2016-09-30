//
//  DSC_Info.cpp
//  PVSC_Parser
//
//  Created by s117 on 16/9/30.
//  Copyright © 2016年 s117. All rights reserved.
//

#include <stdio.h>
#include "DSC_Info.h"
#include "PVSC_Parser.h"
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
    "STAR_DOUBLE",
    "STAR_CHANCE",
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

DSC_Info::~DSC_Info(){
    PVSC_Parser::free_info(this);
}
