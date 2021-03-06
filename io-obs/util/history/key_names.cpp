/**
 * This file is part of input-overlay
 * which is licensed under the MPL 2.0 license
 * See LICENSE or mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 */

#include <obs-module.h>
#include "key_names.hpp"
#include "../../../ccl/ccl.hpp"

void key_names::load_from_file(const char* path)
{
    auto cfg = new ccl_config(path, "");

    if (!cfg->is_empty())
    {
        auto node = cfg->get_first();

        if (!node)
        {
            delete cfg;
            return;
        }

        do
        {
            if (node->get_type() == ccl_type_string)
            {
                auto val = node->get_id();
                uint16_t key_code = std::stoul(val, nullptr, 16);
                m_names[key_code] = node->get_value();
            }
        } while ((node = node->get_next()) != nullptr);
    }

    if (cfg->has_errors())
        blog(LOG_WARNING, "[input-overlay] %s", cfg->get_error_message().c_str());

    delete cfg;    
}

const char* key_names::get_name(const uint16_t vc)
{
    if (m_names.find(vc) != m_names.end())
    {
        return m_names[vc].c_str();
    }
    return nullptr;
}
