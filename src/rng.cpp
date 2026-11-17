#include <rhatt/util/rng.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

bool rng::flip() {
    return internal::generate<bool>();
}

uint8_t rng::fast() {
    return get<uint8_t>(100, 0);
}

bool rng::chance(uint8_t percent) {
    percent = std::clamp(percent, (uint8_t)0, (uint8_t)100);
    return get(100) <= percent;
}

float rng::pc(size_t precision) {
    auto factor = std::powf(10.0f, precision);
    return std::round(get(1.0f) * factor) / factor;
}

constexpr float rng::chanceToDelayPct(uint8_t chance) noexcept {
    chance = std::clamp(chance, (uint8_t)0, (uint8_t)100);
    return 1.0f - ((float)chance / 100.0f);
}