#pragma once

#include <memory>
#include "plugin.hpp"


#ifdef BIRD_API
#define BIRD_API extern "C" __declspec(dllimport)
#else
#define BIRD_API extern "C" __declspec(dllexport)
#endif  // BIRD_API


namespace bird {

    struct bird_plugin : public pe::plugin {
        bird_plugin();
        ~bird_plugin() override;

        void execute() const override;
        void release() override;
    };

    BIRD_API pe::plugin* create_object();

} // namespace bird
