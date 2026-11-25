#pragma once

#include <matjson.hpp>

#include <Geode/cocos/cocoa/CCGeometry.h>

template <>
struct matjson::Serialize<cocos2d::CCPoint> final {
    static geode::Result<cocos2d::CCPoint> fromJson(Value const& value);
    static matjson::Value toJson(cocos2d::CCPoint const& value);
};

template <>
struct matjson::Serialize<cocos2d::CCSize> final {
    static geode::Result<cocos2d::CCSize> fromJson(Value const& value);
    static matjson::Value toJson(cocos2d::CCSize const& value);
};