#pragma once

#include <memory>
#include "plugin.hpp"


#ifndef KANGAROO_API
#define KANGAROO_API extern "C" __declspec(dllimport)
#endif  // KANGAROO_API


namespace kangaroo {

    struct kangaroo_plugin : public pe::plugin {
        kangaroo_plugin();
        ~kangaroo_plugin() override;

        void execute() const override;
        void release() override;
    };

    KANGAROO_API pe::plugin* create_object();

} // namespace kangaroo
