#ifndef _WTF_BASE_DANMAKU_HPP
#define _WTF_BASE_DANMAKU_HPP

#include <cstdint>
#include <string>
#include <memory>
#include "Noncopyable.hpp"
#include "GlobalConfig.hpp"
#include "Rect.hpp"

using std::shared_ptr;
using std::weak_ptr;

namespace WTFDanmaku {

    enum DanmakuType {
        kNull = 0,
        kScrolling = 1,
        kBottom = 4,
        kTop = 5,
        kReverse = 6,
        kPosition = 7,
        kAdvanced = 8
    };

    class Displayer;
    class Renderable;
    
    class BaseDanmaku : public Noncopyable {
        friend class DanmakuFactory;
        friend class Renderable;
    public:
        explicit BaseDanmaku();

        virtual ~BaseDanmaku();

        inline float GetWidth() {
            return mTextWidth;
        }

        inline float GetHeight() {
            return mTextHeight;
        }

        bool HasMeasured();

        inline bool HasLayout() {
            return mHasLayout;
        }

        inline bool HasRenderable() {
            return mRenderable != nullptr;
        }

        weak_ptr<Renderable> BuildRenderable();

        inline weak_ptr<Renderable> GetRenderable() {
            return weak_ptr<Renderable>(mRenderable);
        }

        inline void ReleaseRenderable() {
            mRenderable.reset();
        }

        virtual void ReleaseResources();

        virtual void Measure(Displayer* displayer);

        virtual void Layout(Displayer* displayer, float x, float y) = 0;

        virtual DanmakuType GetType() = 0;

        virtual bool IsAlive(time_t time);

        virtual float GetSpeed() = 0;

        virtual float GetLeftAtTime(Displayer* displayer, time_t time) = 0;

        virtual Rect<float> GetRectAtTime(Displayer* displayer, time_t time) = 0;

        inline time_t GetStartTime() {
            return mStartTime;
        }

        inline Rect<float> GetRect() {
            return mRect;
        }

        inline time_t GetSendTimestamp() {
            return mTimestamp;
        }

        inline uint32_t GetDanmakuId() {
            return mDanmakuId;
        }
    protected:
        time_t mStartTime = 0;
        Rect<float> mRect;
        float mTextWidth = -1.0f;
        float mTextHeight = -1.0f;
        bool mHasLayout = false;
    private:
        std::wstring mComment;
        float mTextSize = 0.0f;
        uint32_t mTextColor = 0;
        uint32_t mTextShadowColor = 0;
        uint32_t mFilterParams = 0;
        time_t mTimestamp = 0;
        uint32_t mDanmakuId = 0;
        shared_ptr<Renderable> mRenderable = nullptr;
    };

    typedef shared_ptr<BaseDanmaku> DanmakuRef;

}

#endif // _WTF_BASE_DANMAKU_HPP