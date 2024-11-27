#pragma once
#include "MetalReference.h"
#include "Renderer.h"

// MyMTKViewDelegate using dependency injection
class MyMTKViewDelegate : public MTK::ViewDelegate
{
public:
    MyMTKViewDelegate(MTL::Device *pDevice);
    virtual ~MyMTKViewDelegate() override;
    virtual void drawInMTKView(MTK::View *pView) override;

private:
    Renderer *_pRenderer;
};