#pragma once

#include "../Macros.h"

#include "../util.hpp"

#include <Geode/utils/string.hpp>

namespace cw {
    namespace str {
        using namespace geode::utils::string;

        inline constexpr auto isOnOff(bool on) {
            return on ? "ON" : "OFF";
        }

        template <Number T>
        std::string fmtNum(T num, std::optional<size_t> precision = std::nullopt) {
            if constexpr (std::is_floating_point_v<T>) {
                if (precision.has_value()) return fmt::format("{:.{}f}", num, *precision);
            }

            return fmt::to_string(num);
        }

        namespace plurals {
            std::string appendS(std::string_view word, uint64_t amount, bool uppercase = false);
            std::string versatile(std::string_view singular, std::string_view plural, uint64_t amount);
        };
    };

#ifdef CW_GEODE_ID
    namespace internal {
        // stole this from gode :3c
        template <size_t N>
        struct StringConcatGeodeID final {
            static constexpr auto extra = sizeof(CW_GEODE_ID);
            char buffer[extra + N]{};
            constexpr StringConcatGeodeID(const char (&pp)[N]) {
                char id[] = CW_GEODE_ID;
                for (size_t i = 0; i < sizeof(id); ++i) {
                    buffer[i] = id[i];
                };

                buffer[extra - 1] = '/';
                for (size_t i = 0; i < N; ++i) {
                    buffer[extra + i] = pp[i];
                };
            }
        };
    };
#endif
};

#ifdef CW_GEODE_ID
template <cw::internal::StringConcatGeodeID Str>
constexpr auto operator""_gode() {
    return Str.buffer;
}
#endif