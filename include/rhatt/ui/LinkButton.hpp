#pragma once

#include <Geode/ui/Button.hpp>

namespace cw::ui {
    struct LinkButton final {
        std::string id;
        std::string sprite;
        geode::Button::ButtonCallback callback;
    };
};