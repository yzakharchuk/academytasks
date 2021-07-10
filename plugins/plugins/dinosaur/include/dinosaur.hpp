#pragma once

#include <memory>
#include "plugin.hpp"


#ifndef DINOSAUR_API
#define DINOSAUR_API extern "C" __declspec(dllimport)
#endif  // DINOSAUR_API


namespace dinosaur {

    struct dinosaur_plugin : public pe::plugin {
        dinosaur_plugin();
        ~dinosaur_plugin() override;

        void execute() const override;
        void release() override;
    };

    DINOSAUR_API pe::plugin* create_object();

} // namespace dinosaur
