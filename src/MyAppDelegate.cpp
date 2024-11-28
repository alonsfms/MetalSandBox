
#include "MetalReference.h"
#include "MyAppDelegate.h"

bool MyAppDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application *pSender)
{
    return true;
}

void MyAppDelegate::applicationWillFinishLaunching(NS::Notification *pNotification)
{
    NS::Menu *pMenu = createMenuBar();
    NS::Application *pApp = reinterpret_cast<NS::Application *>(pNotification->object());
    pApp->setMainMenu(pMenu);
    pApp->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
}

MyAppDelegate::~MyAppDelegate()
{
    _pMtkView->release();
    _pWindow->release();
    _pDevice->release();
    delete _pViewDelegate;
}

NS::Menu *MyAppDelegate::createMenuBar()
{

    NS::Menu *pMainMenu = NS::Menu::alloc()->init();
    NS::MenuItem *pAppMenuItem = NS::MenuItem::alloc()->init();
    NS::Menu *pAppMenu = NS::Menu::alloc()->init(NS::String::string("Appname", NS::StringEncoding::UTF8StringEncoding));

    NS::String *appName = NS::RunningApplication::currentApplication()->localizedName();
    NS::String *quitItemName = NS::String::string("Quit ", NS::StringEncoding::UTF8StringEncoding)->stringByAppendingString(appName);
    SEL quitCb = NS::MenuItem::registerActionCallback("appQuit", [](void *, SEL, const NS::Object *pSender)
                                                      {
        auto pApp = NS::Application::sharedApplication();
        pApp->terminate( pSender ); });

    NS::MenuItem *pAppQuitItem = pAppMenu->addItem(quitItemName, quitCb, NS::String::string("q", NS::StringEncoding::UTF8StringEncoding));
    pAppQuitItem->setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);
    pAppMenuItem->setSubmenu(pAppMenu);

    NS::MenuItem *pWindowMenuItem = NS::MenuItem::alloc()->init();
    NS::Menu *pWindowMenu = NS::Menu::alloc()->init(NS::String::string("Window", NS::StringEncoding::UTF8StringEncoding));

    SEL closeWindowCb = NS::MenuItem::registerActionCallback("windowClose", [](void *, SEL, const NS::Object *)
                                                             {
        auto pApp = NS::Application::sharedApplication();
            pApp->windows()->object< NS::Window >(0)->close(); });
    NS::MenuItem *pCloseWindowItem = pWindowMenu->addItem(NS::String::string("Close Window", NS::StringEncoding::UTF8StringEncoding), closeWindowCb, NS::String::string("w", NS::StringEncoding::UTF8StringEncoding));
    pCloseWindowItem->setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);

    pWindowMenuItem->setSubmenu(pWindowMenu);

    pMainMenu->addItem(pAppMenuItem);
    pMainMenu->addItem(pWindowMenuItem);

    pAppMenuItem->release();
    pWindowMenuItem->release();
    pAppMenu->release();
    pWindowMenu->release();

    return pMainMenu->autorelease();
}

/// @brief Creates the window, a menu, and the Metal-capable content view.
/// @param pNotification
void MyAppDelegate::applicationDidFinishLaunching(NS::Notification *pNotification)
{
    // Set window position and size
    CGRect frame = (CGRect){{0.0, 0.0}, {512.0, 512.0}};

    // Set window member variable
    _pWindow = NS::Window::alloc()->init(
        frame,
        NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled,
        NS::BackingStoreBuffered,
        false);

    // Sets MTL::Devices, a software representation of the system's GPU
    _pDevice = MTL::CreateSystemDefaultDevice();

    // Configures the MTK::View object to display metal content in a window
    _pMtkView = MTK::View::alloc()->init(frame, _pDevice);
    _pMtkView->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    _pMtkView->setClearColor(MTL::ClearColor::Make(0.25, 0.0, 0.0, 1.0));

    // Sets the MTK::MyViewDelegate object, which is a subclass of MTK::ViewDelegate, this class
    // provides an interface to which the MTK::View can forward events, by overwritting virtual
    // functions of its parents class, MyMTKViewDelegate can respond to these events. MTK::View (parent class)
    // calls the drawInMTKView() method each fram allowing the app to update any rendering,
    // this object is the one that calls the drawInMTKView
    _pViewDelegate = new MyMTKViewDelegate(_pDevice);
    _pMtkView->setDelegate(_pViewDelegate);

    _pWindow->setContentView(_pMtkView);
    _pWindow->setTitle(NS::String::string("My First Metal Window", NS::StringEncoding::UTF8StringEncoding));

    _pWindow->makeKeyAndOrderFront(nullptr);

    NS::Application *pApp = reinterpret_cast<NS::Application *>(pNotification->object());
    pApp->activateIgnoringOtherApps(true);
}
