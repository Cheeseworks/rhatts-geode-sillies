#pragma once

#include <algorithm>

#include <Geode/cocos/include/ccTypes.h>

namespace cw {
    namespace colors {
        inline constexpr cocos2d::ccColor3B white = { 255, 255, 255 };
        inline constexpr cocos2d::ccColor3B gray = { 150, 150, 150 };
        inline constexpr cocos2d::ccColor3B red = { 225, 75, 100 };
        inline constexpr cocos2d::ccColor3B yellow = { 250, 250, 25 };
        inline constexpr cocos2d::ccColor3B green = { 100, 255, 100 };
        inline constexpr cocos2d::ccColor3B cyan = { 10, 175, 255 };
        inline constexpr cocos2d::ccColor3B blue = { 0, 122, 255 };
        inline constexpr cocos2d::ccColor3B pink = { 233, 89, 161 };
        inline constexpr cocos2d::ccColor3B purple = { 106, 25, 200 };
        inline constexpr cocos2d::ccColor3B gold = { 255, 200, 150 };
        inline constexpr cocos2d::ccColor3B black = { 25, 25, 25 };

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
            value = std::clamp(value, 0.f, 100.f);

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