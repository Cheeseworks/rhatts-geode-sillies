#pragma once

#include "../util/strings.hpp"

#include "../ui/consts.hpp"

#include <Geode/ui/Button.hpp>

#include <Geode/binding/ProfilePage.hpp>
#include <Geode/binding/FLAlertLayer.hpp>

namespace cw::ui {
    geode::Button* addHelpButton(cocos2d::CCNode* to, std::string content, bool useMarkdown = false, float btnScale = 0.75f, cocos2d::CCPoint const& offset = {});

    ProfilePage* showProfile(int accountID, bool ownProfile = false);

    namespace popups {
        FLAlertLayer* showDiscord();
        void showSupport();
    };

    geode::Button* createProfileBtn(GJUserScore* user, geode::ZStringView font = cw::ui::font::big);
    geode::Button* createProfileBtn(std::string username, int accountID, geode::ZStringView font = cw::ui::font::big);
};