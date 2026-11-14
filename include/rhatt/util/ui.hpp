#pragma once

#include "strings.hpp"

#include <Geode/ui/Button.hpp>

#include <Geode/binding/FLAlertLayer.hpp>

namespace cw {
    namespace ui {
        struct LinkButton final {
            std::string id;
            std::string sprite;
            geode::Button::ButtonCallback callback;
        };

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

        namespace nodes {
            geode::Button* addHelpButton(cocos2d::CCNode* to, std::string content, bool useMarkdown = false, float btnScale = 0.75f, cocos2d::CCPoint const& offset = {});
        };

        namespace popups {
            FLAlertLayer* showDiscord();
            void showSupport();
        };
    };
};