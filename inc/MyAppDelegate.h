#pragma once
#include "MetalReference.h"
#include "MyMTKViewDelegate.h"

// MyAppDeletage using dependency injection, notice this is
// a child class from interface NS::ApplicationDelegate
class MyAppDelegate : public NS::ApplicationDelegate
{
public:
    ~MyAppDelegate();

    NS::Menu *createMenuBar();

    virtual void applicationWillFinishLaunching(NS::Notification *pNotification) override;
    virtual void applicationDidFinishLaunching(NS::Notification *pNotification) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application *pSender) override;

private:
    NS::Window *_pWindow;
    MTK::View *_pMtkView;  // used to display Metal content in a window
    MTL::Device *_pDevice; // Software representation of the system's GPU
    MyMTKViewDelegate *_pViewDelegate = nullptr;
};
