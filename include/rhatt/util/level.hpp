#pragma once

#include <cstdint>

#include <Geode/Enums.hpp>

namespace cw {
    namespace lvl {
        enum class Rating : uint8_t {
            None = 0,
            Star = 1,
            Featured = 2,
            Epic = 3,
            Legendary = 4,
            Mythic = 5,
        };

        inline constexpr auto getLengthText(int length, bool plat = false) {
            if (plat) return "Plat.";

            switch (length) {
                default: [[fallthrough]];

                case 0: return "Tiny";
                case 1: return "Short";
                case 2: return "Medium";
                case 3: return "Long";
                case 4: return "XL";
            };
        }

        inline constexpr auto getFeatureState(Rating r) {
            switch (r) {
                case Rating::None: return GJFeatureState::None;
                case Rating::Star: return GJFeatureState::None;
                case Rating::Featured: return GJFeatureState::Featured;
                case Rating::Epic: return GJFeatureState::Epic;
                case Rating::Legendary: return GJFeatureState::Legendary;
                case Rating::Mythic: return GJFeatureState::Mythic;
            };
        }
    };
};