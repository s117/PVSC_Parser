#ifndef __H_INST_PLUGIN_INTERFACE
#define __H_INST_PLUGIN_INTERFACE

#include "GlobalDef.h"
#include "EngineCore.h"

class EngineCore;

class InstPluginInterface {
public:
    virtual bool register_inst(IN EngineCore* engine, OUT uint32_t* opcode) = 0;
    virtual bool unregister_inst(IN EngineCore* engine) = 0;
    virtual STEP parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence) = 0;
};

#endif
