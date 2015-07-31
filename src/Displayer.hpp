#ifndef _WTF_DISPLAYER_HPP
#define _WTF_DISPLAYER_HPP

#include <wrl.h>
#include <d2d1_1.h>
#include <cstdint>
#include <memory>
#include "BaseDanmaku.hpp"
#include "Noncopyable.hpp"

using Microsoft::WRL::ComPtr;

namespace WTFDanmaku {

    class DisplayerImpl;

    class Displayer : public Noncopyable {
    public:
        explicit Displayer();
        ~Displayer();
        void SetTarget(void* windowHandle);
        bool SetupBackend();
        bool TeardownBackend();
        int GetWidth();
        int GetHeight();
        float GetDpiX();
        float GetDpiY();
        void Resize(int width, int height);
        ComPtr<ID2D1Bitmap1> CreateBitmap(float width, float height);
        ComPtr<ID2D1RenderTarget> ObtainRenderTarget(ComPtr<ID2D1Bitmap1> bitmap);
        void DrawDanmakuItem(DanmakuRef item, time_t current);
        void BeginDraw();
        HRESULT EndDraw();
    private:
        std::unique_ptr<DisplayerImpl> pImpl;
    };

}

#endif // _WTF_DISPLAYER_HPP