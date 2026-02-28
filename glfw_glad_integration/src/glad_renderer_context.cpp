#include "engine.hpp"
#include "gg_integration.hpp"

namespace {
    int width, height;

    void onFramebufferSizeEvent(GLFWwindow *window, int newWidth, int newHeight) {
        width = newWidth;
        height = newHeight;
    }
}

namespace cppengine {
    GladRendererContext::GladRendererContext() {
        gladLoadGL(glfwGetProcAddress);
        modelContext = new GladModelContext();
        shaderContext = new GladShaderContext();
        textureContext = new GladTextureContext();
        GLFWwindow *window = GGContextManager::getWindowContext()->getWindow();
        glfwGetFramebufferSize(window, &width, &height);
        glfwSetFramebufferSizeCallback(window, &onFramebufferSizeEvent);

        glClearColor(0,0,0,1);

    }

    ObjectHandle<TextureContext> GladRendererContext::getTextureContext() const {
        return textureContext;
    }

    ObjectHandle<ModelContext> GladRendererContext::getModelContext() const {
        return modelContext;
    }

    ObjectHandle<ShaderContext> GladRendererContext::getShaderContext() const {
        return shaderContext;
    }

    ObjectHandle<DrawContext> GladRendererContext::createDrawContext(
        const Rectangle2D &absoluteViewport, const Matrix4x4 &transform) {
        return new GladDrawContext(absoluteViewport, transform);
    }

    std::pair<int, int> GladRendererContext::getFrameBufferSize() const {
        return { width, height };
    }

    void GladRendererContext::beginDraw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GladRendererContext::endDraw() {
        glfwSwapBuffers(GGContextManager::getWindowContext()->getWindow());
    }

    GladRendererContext::~GladRendererContext() {

    }
}
