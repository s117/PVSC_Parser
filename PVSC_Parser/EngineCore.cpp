#define __C_ENGINE_CORE
#include "EngineCore.h"


EngineCore::EngineCore() {}
EngineCore::~EngineCore() {
    instruction_map_t::iterator it;
    for (it = this->m_map_insts.begin(); it != this->m_map_insts.end(); ++it) {
        it->second->unregister_inst(this);
    }
}

ERR_CODE EngineCore::add_inst(IN InstPluginInterface* plugin) {
    if (plugin != nullptr) {
        uint32_t opcode;
        if (plugin->register_inst(this, &opcode)) {
            m_map_insts[opcode] = plugin;
            return CODE_OK;
        }
    }
    return CODE_ERR_INVALID_ARGS;
}

// len must be 4 byte aligned
ERR_CODE EngineCore::set_sequence(IN uint8_t const *sequence, IN uint32_t len) {
    if ((sequence != nullptr) && ((len & 0x3) == 0)) {
        this->m_sequence = sequence;
        this->m_len = len;
        return CODE_OK;
    } else {
        return CODE_ERR_INVALID_ARGS;
    }

}

const uint8_t* EngineCore::get_sequence() {
    return this->m_sequence;
}

ERR_CODE EngineCore::set_offset(IN uint32_t offset) {
    if (m_sequence == nullptr)
        return STEP_SEQUENCE_UNSET;
    this->m_pos = offset;
    return CODE_OK;
}

uint32_t EngineCore::get_offset() {
    return this->m_pos;
}

STEP EngineCore::step() {
    if (m_sequence == nullptr)
        return STEP_SEQUENCE_UNSET;
    InstPluginInterface* inst;
    uint8_t const *cur_parse_pos = m_sequence + m_pos;
    uint32_t len_remaining = m_len - m_pos;
    int32_t rtnval;

    if (len_remaining == 0)
        return STEP_END_OF_SEQUENCE;

    inst = m_map_insts[*(uint32_t*)cur_parse_pos];
    if (inst == nullptr)
        return STEP_UNKNOW_INSTRUCTION;

    rtnval = inst->parse_inst(cur_parse_pos, len_remaining);
    if (rtnval&(1 << 31)) {
        return rtnval;
    } else {
        m_pos += rtnval;
        return rtnval;
    }
}

bool EngineCore::set_endian(ENDIAN_TYPE type) {
    this->m_endian_type = type;
    return true;
}

ENDIAN_TYPE EngineCore::get_endian() {
    return this->m_endian_type;
}
