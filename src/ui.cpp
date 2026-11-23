#include <rhatt/ui/utils.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;
using namespace cw;

FLAlertLayer* ui::showAlert(ZStringView title, std::string content, ZStringView btn1, std::optional<ZStringView> btn2, AlertCallback callback, float width, bool cancelledByEscape) {
    return createQuickPopup(title, std::move(content), btn1, btn2.value_or(ZStringView{ nullptr }), width, std::move(callback), true, cancelledByEscape);
}

Button* ui::addHelpButton(CCNode* to, std::string content, bool useMarkdown, float btnScale, CCPoint const& offset) {
    auto infoBtn = Button::createWithSpriteFrameName(
        sprites::info,
        [cont = std::move(content), useMarkdown](auto) {
            if (useMarkdown) return MDPopup::create(
                                        true,
                                        "Help",
                                        cont,
                                        "OK",
                                        nullptr,
                                        nullptr
            )
                ->show();

            showAlert(
                "Help",
                cont,
                "OK"
            );
        }
    );
    infoBtn->setID("info-btn");
    infoBtn->setScale(btnScale);
    infoBtn->setZOrder(CW_HIGHEST_Z);

    to->addChildAtPosition(infoBtn, Anchor::TopRight, CCPoint{ -15.0f, -15.0f } + offset, false);
    return infoBtn;
}

ProfilePage* ui::showProfile(int accountID, bool ownProfile) {
    auto popup = ProfilePage::create(accountID, ownProfile);
    popup->show();

    return popup;
}

Button* ui::createProfileBtn(GJUserScore* user, ZStringView font) {
    return createProfileBtn(user->m_userName, user->m_accountID, font);
}

Button* ui::createProfileBtn(std::string username, int accountID, ZStringView font) {
    auto btn = Button::createWithLabel(
        std::move(username),
        font,
        [accountID](auto) {
            showProfile(accountID);
        }
    );
    btn->setID("view-profile-btn");
    btn->setScaleMultiplier(1.125f);

    return btn;
}

FLAlertLayer* ui::popups::showDiscord() {
    return showAlert(
        "Discord Community",
        "Join <cd>Cheeseworks</c>'s <cb>Discord server</c>?\n"
        "<cs>Get help, report bugs, and chat with other players!</c>",
        "Cancel",
        "OK",
        [](auto, bool ok) {
            if (ok) web::openLinkInBrowser("https://www.dsc.gg/cheeseworks");
        }
    );
}

void ui::popups::showSupport() {
    return openSupportPopup(Mod::get());
}