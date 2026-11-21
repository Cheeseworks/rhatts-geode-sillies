#pragma once

#include <Geode/ui/LazySprite.hpp>

namespace cw::ui {
    class WebSprite final : public cocos2d::CCNodeRGBA {
        struct Impl;
        std::unique_ptr<Impl> m_impl;

    protected:
        WebSprite();
        ~WebSprite();

        bool init(cocos2d::CCSize size, bool loadingCircle);

    public:
        using LoadResult = geode::Result<geode::ByteVector>;

        using LoadCallback = geode::Function<void(LoadResult)>;
        using LoadFuture = arc::Future<LoadResult>;

        static WebSprite* create(cocos2d::CCSize size, bool loadingCircle = true);

        void setRequestInfo(geode::utils::web::WebRequest request);

        void load(std::string url, LoadCallback callback);

        LoadFuture loadData(std::string url);

        void cancelLoad();

        void resetImage();

        geode::utils::web::WebRequest const& getRequestInfo() const noexcept;
        geode::ByteVector getImageData() const noexcept;
    };
};