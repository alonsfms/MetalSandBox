#include "Renderer.h"

Renderer::Renderer(MTL::Device *pDevice)
    : _pDevice(pDevice->retain())
{
    _pCommandQueue = _pDevice->newCommandQueue();
}

Renderer::~Renderer()
{
    _pCommandQueue->release();
    _pDevice->release();
}

// Frame
void Renderer::draw(MTK::View *pView)
{
    // Metal relies on temporary autoreleased objectes, the sample creates a NS::AutoreleasePool object
    // at the beginning to manage these objects. This pool tracks these temporary objects and frees
    // them when the pool descturctors is called at the end of the frame.
    NS::AutoreleasePool *pPool = NS::AutoreleasePool::alloc()->init();
    // Create a command buffer object. Allows the app to encode commands for execution by the GPU
    MTL::CommandBuffer *pCmd = _pCommandQueue->commandBuffer();

    MTL::RenderPassDescriptor *pRpd = pView->currentRenderPassDescriptor();

    // Creates a Renderer command encoder object. Prepares the command buffer to receive drwaing commands
    // and specifies the the actions to perform when drwaing starts and ends. The MTL RendererCommandEncoder
    // does not explicitly encode any commands. However, the MTL::RenderPassDescriptor object uset to
    // create the encoder implicitly encodes a clear command. The command prodcues the solid red color
    // on the view.
    MTL::RenderCommandEncoder *pEnc = pCmd->renderCommandEncoder(pRpd);
    pEnc->endEncoding();
    // Presents the current drawable. Encodes a command to make the results of the GPU's work vistible
    // on the screen
    pCmd->presentDrawable(pView->currentDrawable());
    pCmd->commit();

    pPool->release();
}