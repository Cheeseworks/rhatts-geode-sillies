#include <rhatt/util/DelegateDirector.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

void DelegateDirector::loadLevelsFinished(CCArray* search, const char* key, int) {
    GameLevelManager::sharedState()->m_levelManagerDelegate = nullptr;

    log::trace("Received finished request with key {}", key);

    if (auto const it = m_levelCallbacks.find(key); it != m_levelCallbacks.end()) {
        auto array = search->asExt<GJGameLevel*>();
        if (array.empty()) return it->second(Err("No results found"));

        it->second(Ok(array[0]));
        m_levelCallbacks.erase(it);

        log::debug("Cleaned up level callback entry for key {}", key);

    } else if (auto const it = m_userCallbacks.find(key); it != m_userCallbacks.end()) {
        auto array = search->asExt<GJUserScore*>();
        if (array.empty()) return it->second(Err("No results found"));

        it->second(Ok(array[0]));
        m_userCallbacks.erase(it);

        log::debug("Cleaned up user callback entry for key {}", key);

    } else if (auto const it = m_levelListCallbacks.find(key); it != m_levelListCallbacks.end()) {
        it->second(Ok(search->asExt<GJGameLevel*>()));
        m_levelListCallbacks.erase(it);

        log::debug("Cleaned up level list callback entry for key {}", key);
    };
}

void DelegateDirector::loadLevelsFailed(const char* key, int) {
    GameLevelManager::sharedState()->m_levelManagerDelegate = nullptr;

    log::warn("Received failed request with key {}", key);

    if (auto const it = m_levelCallbacks.find(key); it != m_levelCallbacks.end()) {
        it->second(Err("Request failed"));
        m_levelCallbacks.erase(it);

        log::debug("Cleaned up level callback entry for key {}", key);

    } else if (auto const it = m_userCallbacks.find(key); it != m_userCallbacks.end()) {
        it->second(Err("Request failed"));
        m_userCallbacks.erase(it);

        log::debug("Cleaned up user callback entry for key {}", key);

    } else if (auto const it = m_levelListCallbacks.find(key); it != m_levelListCallbacks.end()) {
        it->second(Err("Request failed"));
        m_levelListCallbacks.erase(it);

        log::debug("Cleaned up level list callback entry for key {}", key);
    };
}

void DelegateDirector::levelDownloadFinished(GJGameLevel* level) {
    GameLevelManager::sharedState()->m_levelDownloadDelegate = nullptr;

    log::trace("Received finished level download request for level ID {}", level->m_levelID);

    if (auto const it = m_levelDownloadCallbacks.find(level->m_levelID); it != m_levelDownloadCallbacks.end()) {
        if (it->second.empty()) return log::error("No callbacks found for level ID {}", level->m_levelID);

        for (auto& cb : it->second) cb(Ok(level));
        m_levelDownloadCallbacks.erase(it);

        log::debug("Cleared callback list for level ID {}", level->m_levelID);
    };
}

void DelegateDirector::levelDownloadFailed(int response) {  // ???
    GameLevelManager::sharedState()->m_levelDownloadDelegate = nullptr;

    log::warn("Received failed level download request with response code {}", response);
}

void DelegateDirector::getUserInfoFinished(GJUserScore* score) {
    GameLevelManager::sharedState()->m_userInfoDelegate = nullptr;

    log::trace("Received finished request for account ID {}", score->m_accountID);

    if (auto const it = m_userIDCallbacks.find(score->m_accountID); it != m_userIDCallbacks.end()) {
        if (it->second.empty()) return log::error("No callbacks found for account ID {}", score->m_accountID);

        for (auto& cb : it->second) cb(Ok(score));
        m_userIDCallbacks.erase(it);

        log::debug("Cleared callback list for account ID {}", score->m_accountID);
    };
}

void DelegateDirector::getUserInfoFailed(int id) {
    GameLevelManager::sharedState()->m_userInfoDelegate = nullptr;

    log::warn("Received failed request for account ID {}", id);

    if (auto const it = m_userIDCallbacks.find(id); it != m_userIDCallbacks.end()) {
        if (it->second.empty()) return log::error("No callbacks found for account ID {}", id);

        for (auto& cb : it->second) cb(Err("Request failed"));
        m_userIDCallbacks.erase(it);

        log::debug("Cleared callback list for account ID {}", id);
    };
}

void DelegateDirector::userInfoChanged(GJUserScore* score) {
}

void DelegateDirector::getUserListFinished(CCArray* scores, UserListType type) {
    GameLevelManager::sharedState()->m_userListDelegate = nullptr;

    if (auto const it = m_userListCallbacks.find(type); it != m_userListCallbacks.end()) {
        it->second(Ok(scores->asExt<GJUserScore*>()));
        m_userListCallbacks.erase(it);

        log::debug("Cleared callback for user list for type {}", (int)type);
    };
}

void DelegateDirector::getUserListFailed(UserListType type, GJErrorCode errorType) {
    GameLevelManager::sharedState()->m_userListDelegate = nullptr;

    if (auto const it = m_userListCallbacks.find(type); it != m_userListCallbacks.end()) {
        it->second(Err("Request failed with code {}", (int)errorType));
        m_userListCallbacks.erase(it);

        log::debug("Cleared callback for user list for type {}", (int)type);
    };
}

void DelegateDirector::userListChanged(CCArray* scores, UserListType type) {
}

void DelegateDirector::searchLevel(int levelID, LevelCallback callback) {
    auto glm = GameLevelManager::sharedState();

    auto obj = GJSearchObject::create(SearchType::Search, cw::fmtNum(levelID));
    m_levelCallbacks[obj->getKey()] = std::move(callback);

    log::trace("Registered level callback with key '{}'", obj->getKey());

    glm->m_levelManagerDelegate = this;
    glm->getOnlineLevels(obj);
}

void DelegateDirector::searchUser(std::string username, UserCallback callback) {
    auto glm = GameLevelManager::sharedState();

    auto obj = GJSearchObject::create(SearchType::Users, std::move(username));
    m_userCallbacks[obj->getKey()] = std::move(callback);

    log::trace("Registered user callback with key '{}'", obj->getKey());

    glm->m_levelManagerDelegate = this;
    glm->getUsers(obj);
}

void DelegateDirector::searchUserLevels(int userID, int page, LevelListCallback callback) {
    auto glm = GameLevelManager::sharedState();

    auto obj = GJSearchObject::create(SearchType::UsersLevels, cw::fmtNum(userID));
    obj->m_page = page;

    m_levelListCallbacks[obj->getKey()] = std::move(callback);

    log::trace("Registered level list callback with key '{}'", obj->getKey());

    glm->m_levelManagerDelegate = this;
    glm->getOnlineLevels(obj);
}

void DelegateDirector::getUserList(UserListType type, UserListCallback callback) {
    auto glm = GameLevelManager::sharedState();

    if (auto saved = glm->getStoredUserList(type)->asExt<GJUserScore>(); !saved.empty()) return callback(Ok(saved));

    m_userListCallbacks[type] = std::move(callback);

    log::trace("Set user list callback with type {}", (int)type);

    glm->m_userListDelegate = this;
    glm->getUserList(type);
}

void DelegateDirector::downloadLevel(int levelID, LevelCallback callback) {
    auto glm = GameLevelManager::sharedState();

    if (auto saved = glm->getSavedLevel(levelID)) return callback(Ok(saved));

    m_levelDownloadCallbacks[levelID].push_back(std::move(callback));

    log::trace("Pushed level download callback for level ID '{}'", levelID);

    glm->m_levelDownloadDelegate = this;
    glm->downloadLevel(levelID, false, 0);
}

void DelegateDirector::searchUserByID(int accountID, UserCallback callback) {
    auto glm = GameLevelManager::sharedState();

    m_userIDCallbacks[accountID].push_back(std::move(callback));

    log::trace("Pushed user ID callback for account ID '{}'", accountID);

    glm->m_userInfoDelegate = this;
    glm->getGJUserInfo(accountID);
}