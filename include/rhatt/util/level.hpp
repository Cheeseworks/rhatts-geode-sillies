#pragma once

#include <Geode/binding/GJGameLevel.hpp>

namespace cw::lvl {
    enum class Rating : int {
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

    inline constexpr auto getDiffSpriteNum(GJGameLevel* level) {
        if (level->m_demon.value() == 1) {
            switch (level->m_demonDifficulty) {
                default: return 6;

                case 3: return 7;
                case 4: return 8;
                case 5: return 9;
                case 6: return 10;
            };
        };

        if (level->m_autoLevel) return -1;
        return level->getAverageDifficulty();
    }

    inline constexpr auto getRating(GJGameLevel* level) {
        switch (level->m_isEpic) {
            default: break;

            case 1: return Rating::Epic;
            case 2: return Rating::Legendary;
            case 3: return Rating::Mythic;
        };

        if (level->m_featured != 0) return Rating::Featured;
        if (level->m_stars.value() != 0) return Rating::Star;

        return Rating::None;
    }
};