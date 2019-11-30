#pragma once

#include "libopenglwrapperlegacy/IOpenGLWrapperLegacy.hpp"
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2Wrapper/IMPORT_SDL_video.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/GenericUtils/LckPrim.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

NAMESPACE_BEGIN( OGLWL )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
// warning C4820: 'OGLWL::OpenGLWrapperLegacyConcrete': '6' bytes padding added after data member.
#endif

class OpenGLWrapperLegacyConcrete final:
    public IOpenGLwrapperLegacy
{
public:
    explicit OpenGLWrapperLegacyConcrete( SDL2W::ISDL2Wrapper* sdl2w );

protected:
private:
    using CustomSteps = std::map<Cunt, std::function<void()>>;
    using LckBool = CUL::GUTILS::LckBool;

    void mainLoop();
    void initialize() override;
    void beginRenderingLoop() override;
    void endRenderingLoop() override;
    void renderFrame() override;

    void setProjection();
    void clearFrame();
    void clearTransformations();
    void renderObjects();
    void customFrameSteps();
    void updateBuffers();

    void addCustomFrameStep( const std::function<void()>& callback, Cunt id ) override;
    void removeCustomFrameStep( Cunt id ) override;
    const bool customFrameStepExists( Cunt id ) const override;

    void cleanup();
    ~OpenGLWrapperLegacyConcrete();

    ProjectionType m_projectionType = ProjectionType::PERSPECTIVE;
    LckBool m_runMainLoop = true;
    LckBool m_clearEveryFrame = true;
    LckBool m_clearTransformations = true;
    LckBool m_updateBuffers = true;
    
    SDL2W::ISDL2Wrapper* m_sdl2w = nullptr;
    SDL2W::IWindow* m_currentWindow = nullptr;
    SDL_GLContext m_oglContext = nullptr;
    std::thread m_renderingLoopThread;
    CustomSteps m_customSteps;
    double m_fovAngle = 90.0;
    unsigned m_afterFrameSleepMicroSeconds = 12800;

    // Removed.
private:
    OpenGLWrapperLegacyConcrete() = delete;
    OpenGLWrapperLegacyConcrete( const OpenGLWrapperLegacyConcrete& arg ) = delete;
    OpenGLWrapperLegacyConcrete& operator=( const OpenGLWrapperLegacyConcrete& rhv ) = delete;

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( OGLWL )