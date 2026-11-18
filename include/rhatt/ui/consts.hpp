#pragma once

#include "../util/strings.hpp"

namespace cw::ui {
    namespace font {
        inline constexpr auto big = "bigFont.fnt";
        inline constexpr auto gold = "goldFont.fnt";
        inline constexpr auto chat = "chatFont.fnt";

        namespace geode {
            inline constexpr auto mono = "mdFontMono.fnt"_gode;
            inline constexpr auto regular = "mdFont.fnt"_gode;
            inline constexpr auto italic = "mdFontI.fnt"_gode;
            inline constexpr auto bold = "mdFontB.fnt"_gode;
            inline constexpr auto boldItalic = "mdFontBI.fnt"_gode;
        };
    };

    namespace sprites {
        namespace squares {
            inline constexpr auto white = "white-square.png"_gode;
            inline constexpr auto black = "black-square.png"_gode;
        };

        inline constexpr auto close = "close.png"_gode;
        inline constexpr auto info = "GJ_infoIcon_001.png";
    };
};