#include <rhatt/util/cursor.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

void cursor::show() {
    PlatformToolbox::showCursor();  // yea idk just wanna keep the use code consistent
}

void cursor::hide(bool force) {
    if (force || GameManager::sharedState()->getGameVariable(GameVar::LockCursor)) PlatformToolbox::hideCursor();
}