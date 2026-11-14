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

#ifdef CW_GEODE_ID
        namespace internal {
            // stole this from gode :3c
            template <size_t N>
            struct ConcatGeodeID final {
                static constexpr auto extra = std::size(CW_GEODE_ID);
                char buffer[extra + N]{};

                constexpr ConcatGeodeID(const char (&pp)[N]) {
                    std::copy_n(CW_GEODE_ID, extra - 1, buffer);
                    buffer[extra - 1] = '/';
                    std::copy_n(pp, N, buffer + extra);
                }
            };
        };
#endif
    };
};

#ifdef CW_GEODE_ID
template <cw::str::internal::ConcatGeodeID Str>
constexpr auto operator""_gode() {
    return Str.buffer;
}
#endif