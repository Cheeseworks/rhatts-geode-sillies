#pragma once

#include "../ui/utils.hpp"

#include <Geode/utils/random.hpp>

namespace cw::rng {
    namespace internal {
        using namespace geode::utils::random;
    };

    template <Number T = int>
    inline T get(T max, T min = (T)0) {
        if constexpr (std::is_integral_v<T>) return internal::generate<T>(min, max + (T)1);
        return internal::generate<T>(min, max);
    }

    bool flip();

    uint8_t fast();
    bool chance(uint8_t percent);
    float pc(size_t precision = 2);

    inline constexpr float chanceToDelayPct(uint8_t chance) noexcept {
        chance = std::clamp(chance, (uint8_t)0, (uint8_t)100);
        return 1.0f - ((float)chance / 100.0f);
    }
};