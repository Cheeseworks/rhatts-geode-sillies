#pragma once

#include <algorithm>

#include <Geode/cocos/include/ccTypes.h>

namespace cw {
    namespace colors {
        inline constexpr cocos2d::ccColor3B white{ 255, 255, 255 };
        inline constexpr cocos2d::ccColor3B gray{ 150, 150, 150 };
        inline constexpr cocos2d::ccColor3B red{ 225, 75, 100 };
        inline constexpr cocos2d::ccColor3B yellow{ 250, 250, 25 };
        inline constexpr cocos2d::ccColor3B green{ 100, 255, 100 };
        inline constexpr cocos2d::ccColor3B cyan{ 10, 175, 255 };
        inline constexpr cocos2d::ccColor3B blue{ 0, 122, 255 };
        inline constexpr cocos2d::ccColor3B pink{ 233, 89, 161 };
        inline constexpr cocos2d::ccColor3B purple{ 106, 25, 200 };
        inline constexpr cocos2d::ccColor3B gold{ 255, 200, 150 };
        inline constexpr cocos2d::ccColor3B black{ 25, 25, 25 };
        inline constexpr cocos2d::ccColor3B orange{ 255, 165, 0 };
        inline constexpr cocos2d::ccColor3B lime{ 50, 205, 50 };
        inline constexpr cocos2d::ccColor3B teal{ 0, 128, 128 };
        inline constexpr cocos2d::ccColor3B magenta{ 255, 0, 255 };
        inline constexpr cocos2d::ccColor3B indigo{ 75, 0, 130 };
        inline constexpr cocos2d::ccColor3B violet{ 238, 130, 238 };
        inline constexpr cocos2d::ccColor3B maroon{ 128, 0, 0 };
        inline constexpr cocos2d::ccColor3B navy{ 0, 0, 128 };
        inline constexpr cocos2d::ccColor3B olive{ 128, 128, 0 };
        inline constexpr cocos2d::ccColor3B brown{ 165, 42, 42 };
        inline constexpr cocos2d::ccColor3B silver{ 192, 192, 192 };

        namespace internal {
            inline constexpr cocos2d::ccColor3B lerpColor(cocos2d::ccColor3B const& a, cocos2d::ccColor3B const& b, float t) noexcept {
                return {
                    static_cast<GLubyte>(a.r + (b.r - a.r) * t),
                    static_cast<GLubyte>(a.g + (b.g - a.g) * t),
                    static_cast<GLubyte>(a.b + (b.b - a.b) * t),
                };
            }
        };

        inline constexpr cocos2d::ccColor3B fadeColor(float value) noexcept {
            value = std::clamp(value, 0.0f, 100.0f);

            if (value <= 50.0f) {
                auto t = value / 50.0f;
                return internal::lerpColor(red, yellow, t);
            } else {
                auto t = (value - 50.0f) / 50.0f;
                return internal::lerpColor(yellow, green, t);
            };
        }
    };
};