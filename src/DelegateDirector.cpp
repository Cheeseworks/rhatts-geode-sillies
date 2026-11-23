#include <rhatt/util/DelegateDirector.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

void DelegateDirector::loadLevelsFinished(CCArray* search, const char* key, int) {
    GameLevelManager::sharedState()->m_levelManagerDelegate = nullptr;

#ifdef CW_TESTING
    log::trace("Received finished request with key {}", key);
#endif

    if (auto const it = m_levelCallbacks.find(key); it != m_levelCallbacks.end()) {
        auto array = search->asExt<GJGameLevel*>();
        if (array.empty()) return it->second(Err("No results found"));

        it->second(Ok(array[0]));
        m_levelCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleaned up level callback entry for key {}", key);
#endif
    } else if (auto const it = m_userCallbacks.find(key); it != m_userCallbacks.end()) {
        auto array = search->asExt<GJUserScore*>();
        if (array.empty()) return it->second(Err("No results found"));

        it->second(Ok(array[0]));
        m_userCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleaned up user callback entry for key {}", key);
#endif
    } else if (auto const it = m_levelListCallbacks.find(key); it != m_levelListCallbacks.end()) {
        it->second(Ok(search->asExt<GJGameLevel*>()));
        m_levelListCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleaned up level list callback entry for key {}", key);
#endif
    };
}

void DelegateDirector::loadLevelsFailed(const char* key, int) {
    GameLevelManager::sharedState()->m_levelManagerDelegate = nullptr;

    log::warn("Received failed request with key {}", key);

    if (auto const it = m_levelCallbacks.find(key); it != m_levelCallbacks.end()) {
        it->second(Err("Request failed"));
        m_levelCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleaned up level callback entry for key {}", key);
#endif
    } else if (auto const it = m_userCallbacks.find(key); it != m_userCallbacks.end()) {
        it->second(Err("Request failed"));
        m_userCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleaned up user callback entry for key {}", key);
#endif
    } else if (auto const it = m_levelListCallbacks.find(key); it != m_levelListCallbacks.end()) {
        it->second(Err("Request failed"));
        m_levelListCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleaned up level list callback entry for key {}", key);
#endif
    };
}

void DelegateDirector::getUserInfoFinished(GJUserScore* score) {
    GameLevelManager::sharedState()->m_userInfoDelegate = nullptr;

#ifdef CW_TESTING
    log::debug("Received finished request for account ID {}", score->m_accountID);
#endif

    if (auto const it = m_userIDCallbacks.find(score->m_accountID); it != m_userIDCallbacks.end()) {
        if (it->second.empty()) return log::error("No callbacks found for account ID {}", score->m_accountID);

        for (auto& cb : it->second) cb(Ok(score));
        m_userIDCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleared callback list for account ID {}", score->m_accountID);
#endif
    };
}

void DelegateDirector::userInfoChanged(GJUserScore* score) {
}

void DelegateDirector::getUserInfoFailed(int id) {
    GameLevelManager::sharedState()->m_userInfoDelegate = nullptr;

    log::warn("Received failed request for account ID {}", id);

    if (auto const it = m_userIDCallbacks.find(id); it != m_userIDCallbacks.end()) {
        if (it->second.empty()) return log::error("No callbacks found for account ID {}", id);

        for (auto& cb : it->second) cb(Err("Request failed"));
        m_userIDCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleared callback list for account ID {}", id);
#endif
    };
}

void DelegateDirector::getUserListFinished(CCArray* scores, UserListType type) {
    GameLevelManager::sharedState()->m_userListDelegate = nullptr;

    if (auto const it = m_userListCallbacks.find(type); it != m_userListCallbacks.end()) {
        it->second(Ok(scores->asExt<GJUserScore*>()));
        m_userListCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleared callback for user list for type {}", type);
#endif
    };
}

void DelegateDirector::getUserListFailed(UserListType type, GJErrorCode errorType) {
    GameLevelManager::sharedState()->m_userListDelegate = nullptr;

    if (auto const it = m_userListCallbacks.find(type); it != m_userListCallbacks.end()) {
        it->second(Err("Request failed with code {}", (int)errorType));
        m_userListCallbacks.erase(it);

#ifdef CW_TESTING
        log::debug("Cleared callback for user list for type {}", type);
#endif
    };
}

void DelegateDirector::userListChanged(CCArray* scores, UserListType type) {
}

void DelegateDirector::searchLevel(int levelID, LevelCallback callback) {
    auto glm = GameLevelManager::sharedState();

    auto obj = GJSearchObject::create(SearchType::Search, cw::fmtNum(levelID));
    m_levelCallbacks[obj->getKey()] = std::move(callback);

#ifdef CW_TESTING
    log::trace("Registered level callback with key '{}'", obj->getKey());
#endif

    glm->m_levelManagerDelegate = this;
    glm->getOnlineLevels(obj);
}

void DelegateDirector::searchUser(std::string username, UserCallback callback) {
    auto glm = GameLevelManager::sharedState();

    auto obj = GJSearchObject::create(SearchType::Users, std::move(username));
    m_userCallbacks[obj->getKey()] = std::move(callback);

#ifdef CW_TESTING
    log::trace("Registered user callback with key '{}'", obj->getKey());
#endif

    glm->m_levelManagerDelegate = this;
    glm->getUsers(obj);
}

void DelegateDirector::searchUserLevels(int userID, int page, LevelListCallback callback) {
    auto glm = GameLevelManager::sharedState();

    auto obj = GJSearchObject::create(SearchType::UsersLevels, cw::fmtNum(userID));
    obj->m_page = page;

    m_levelListCallbacks[obj->getKey()] = std::move(callback);

#ifdef CW_TESTING
    log::trace("Registered level list callback with key '{}'", obj->getKey());
#endif

    glm->m_levelManagerDelegate = this;
    glm->getOnlineLevels(obj);
}

void DelegateDirector::getUserList(UserListType type, UserListCallback callback) {
    auto glm = GameLevelManager::sharedState();

    m_userListCallbacks[type] = std::move(callback);

#ifdef CW_TESTING
    log::trace("Set user list callback with type {}", (int)type);
#endif

    glm->m_userListDelegate = this;
    glm->getStoredUserList(type);
}

void DelegateDirector::searchUserByID(int accountID, UserCallback callback) {
    auto glm = GameLevelManager::sharedState();

    m_userIDCallbacks[accountID].push_back(std::move(callback));

#ifdef CW_TESTING
    log::trace("Pushed user ID callback for account ID '{}'", accountID);
#endif

    glm->m_userInfoDelegate = this;
    glm->getGJUserInfo(accountID);
}