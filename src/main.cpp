#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include "MetalReference.h"
#include "Renderer.h"
#include "MyMTKViewDelegate.h"
#include "MyAppDelegate.h"

int main( int argc, char* argv[] )
{
    NS::AutoreleasePool* pAutoreleasePool = NS::AutoreleasePool::alloc()->init();

    MyAppDelegate del;

    // Create the gloabl shared app object 
    NS::Application* pSharedApplication = NS::Application::sharedApplication();

    // Initialiaze a custom delegate, it receives notifications of system events, 
    // in particular responds when the app has finished launching and is ready to create its window
    // it has important member variables from metal.
    pSharedApplication->setDelegate( &del );

    // This run calls these method, when calling run
    // - applicationWillFinishLaunching
    // - applicationDidFinishLaunching
    // - applicationShouldTerminateAfterLastWindowClosed

    pSharedApplication->run();

    pAutoreleasePool->release();

    return 0;
}