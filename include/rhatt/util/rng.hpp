#pragma once

#include <rhatt/util.hpp>

#include <Geode/utils/random.hpp>

namespace cw {
    namespace rng {
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

        constexpr float chanceToDelayPct(uint8_t chance) noexcept;
    };
};