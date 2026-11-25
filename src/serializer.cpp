#include <rhatt/util/serializer.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

Result<CCPoint> matjson::Serialize<CCPoint>::fromJson(Value const& value) {
    CCPoint out;

    GEODE_UNWRAP_INTO(out.x, value["x"].asFloat());
    GEODE_UNWRAP_INTO(out.y, value["y"].asFloat());

    return Ok(out);
}

matjson::Value matjson::Serialize<CCPoint>::toJson(CCPoint const& value) {
    Value out;
    out["x"] = value.x;
    out["y"] = value.y;

    return out;
}

Result<CCSize> matjson::Serialize<CCSize>::fromJson(Value const& value) {
    CCSize out;

    GEODE_UNWRAP_INTO(out.width, value["width"].asFloat());
    GEODE_UNWRAP_INTO(out.height, value["height"].asFloat());

    return Ok(out);
}

matjson::Value matjson::Serialize<CCSize>::toJson(CCSize const& value) {
    Value out;
    out["width"] = value.width;
    out["height"] = value.height;

    return out;
}