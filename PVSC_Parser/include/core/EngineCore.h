#ifndef __H_ENGINE_CORE
#define __H_ENGINE_CORE
#include "GlobalDef.h"
#include "InstPluginInterface.h"
#include <list>
#include <map>

class InstPluginInterface;

class EngineCore {
    typedef std::map<uint32_t, InstPluginInterface*> instruction_map_t;
public:
    //Setup part
    EngineCore();
    ~EngineCore();
    ERR_CODE add_inst(IN InstPluginInterface* plugin);

    //Operate part
    ERR_CODE set_sequence(IN uint8_t const *sequence, IN uint32_t sequenceLength);
    const uint8_t* get_sequence();
    ERR_CODE set_offset(IN uint32_t offset);
    uint32_t get_offset();
    STEP step();
    bool set_endian(ENDIAN_TYPE type);
    ENDIAN_TYPE get_endian();
private:
    //std::list<InstPluginInterface*> m_plugin_list;
    instruction_map_t m_map_insts;
    ENDIAN_TYPE m_endian_type = ENDIAN_TYPE::ENDIAN_LE;
    uint32_t m_pos = 0;
    uint32_t m_len = 0;
    const uint8_t* m_sequence = nullptr;
};

#endif
