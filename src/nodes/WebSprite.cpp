#include <rhatt/ui/nodes/WebSprite.hpp>

#include <rhatt/prelude.h>

#include <Geode/Geode.hpp>

using namespace geode::prelude;
using namespace cw;

struct WebSprite::Impl final {
    LazySprite* spr = nullptr;

    CCSize size;
    bool loadingCircle = true;

    LoadCallback callback = nullptr;
    TaskHolder<LoadResult> task;

    ByteVector imgData;

    web::WebRequest request = request::base();
};

WebSprite::WebSprite() : m_impl(std::make_unique<Impl>()) {}
WebSprite::~WebSprite() = default;

bool WebSprite::init(CCSize size, bool loadingCircle) {
    m_impl->size = size;
    m_impl->loadingCircle = loadingCircle;

    if (!CCNodeRGBA::init()) return false;

    setAnchorPoint(anchor::center);
    setContentSize(size);
    ignoreAnchorPointForPosition(false);
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);

    resetImage();

    return true;
}

void WebSprite::onExit() {
    cancelLoad();
    CCNodeRGBA::onExit();
}

void WebSprite::setRequestInfo(web::WebRequest request) {
    m_impl->request = request;
}

void WebSprite::load(std::string url, LoadCallback callback) {
    m_impl->callback = std::move(callback);

    m_impl->task.spawn(
        fmt::format(
            "Image web request for agent {}",
            m_impl->request.getUserAgent().value_or(Mod::get()->getName())
        ),
        loadData(std::move(url)),
        [this](LoadResult res) {
            if (res.isErr()) return m_impl->callback(std::move(res).asErr());

            auto dataSpan = std::move(res).unwrap();
            m_impl->imgData = ByteVector{ dataSpan.begin(), dataSpan.end() };

            m_impl->spr->loadFromData(m_impl->imgData);
        }
    );
}

WebSprite::LoadFuture WebSprite::loadData(std::string url) {
    auto req = co_await m_impl->request.get(std::move(url));
    if (req.error()) co_return Err(req.errorMessage());

    co_return Ok(std::move(req).data());
}

void WebSprite::cancelLoad() {
    m_impl->spr->cancelLoad();
    m_impl->task.cancel();
}

void WebSprite::resetImage() {
    if (m_impl->spr) m_impl->spr->removeFromParent();

    m_impl->spr = LazySprite::create(m_impl->size, m_impl->loadingCircle);
    m_impl->spr->setID("sprite");
    m_impl->spr->setAutoResize(true);

    m_impl->spr->setLoadCallback([this](Result<> res) {
        if (m_impl->callback) {
            if (res.isErr()) return m_impl->callback(std::move(res).asErr());
            m_impl->callback(Ok(m_impl->imgData));
        };
    });

    addChildAtPosition(m_impl->spr, Anchor::Center);
}

web::WebRequest const& WebSprite::getRequestInfo() const noexcept {
    return m_impl->request;
}

geode::ByteVector WebSprite::getImageData() const noexcept {
    return m_impl->imgData;
}

WebSprite* WebSprite::create(CCSize size, bool loadingCircle) {
    auto ret = new WebSprite();
    if (ret->init(size, loadingCircle)) {
        ret->autorelease();
        return ret;
    };

    delete ret;
    return nullptr;
}