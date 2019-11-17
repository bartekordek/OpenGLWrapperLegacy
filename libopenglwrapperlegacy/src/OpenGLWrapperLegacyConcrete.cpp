#include "OpenGLWrapperLegacyConcrete.hpp"
#include "OpenGL_3_Utils.hpp"
#include "IMPORT_SDL_opengl.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace OGLWL;

struct Pos
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

/*
Why not move SDL window create to the guts of OGLWL?
In the future, I want to build a engine which can change
its renderer on the fly.
*/
OpenGLWrapperLegacyConcrete::OpenGLWrapperLegacyConcrete(
    SDL2W::ISDL2Wrapper* sdl2w ):
    m_sdl2w( sdl2w ),
    m_currentWindow( m_sdl2w->getMainWindow() )
{
}

void OpenGLWrapperLegacyConcrete::start()
{
    m_renderingLoopThread = std::thread( &OpenGLWrapperLegacyConcrete::mainLoop, this );
}

void OpenGLWrapperLegacyConcrete::signalStop()
{
    m_runMainLoop = false;
    if( m_renderingLoopThread.joinable() )
    {
        m_renderingLoopThread.join();
    }
    else
    {
        CUL::Assert::simple( false, "Thread OpenGLWrapperLegacyConcrete::mainLoop is joinable." );
    }
}

void OpenGLWrapperLegacyConcrete::mainLoop()
{
    initialize();
    while( m_runMainLoop )
    {
        if( m_clearEveryFrame ) clearFrame();
        renderFrame();
        customFrameSteps();
        if( m_updateBuffers ) updateBuffers();
    }
    cleanup();
}

void OpenGLWrapperLegacyConcrete::initialize()
{
    m_oglContext = SDL_GL_CreateContext( *m_currentWindow );
    auto versionString = UTILS::initContextVersion( 1, 4 );
    std::cout << "Version info: \n" << versionString.string();
    setProjection();
}

void OpenGLWrapperLegacyConcrete::setProjection()
{
    UTILS::resetMatrixToIdentity( GL_PROJECTION );
    UTILS::ViewPortRect vpr;
    vpr.size = m_currentWindow->getSize();
    UTILS::setViewPort( vpr );
    if( ProjectionType::PERSPECTIVE == m_projectionType )
    {
        gluPerspective( m_fovAngle, m_currentWindow->getScreenRatio(), 0, 20 );
    }
    UTILS::resetMatrixToIdentity( GL_MODELVIEW );
    Pos eye;
    eye.z = 10.f;
    Pos center;
    Pos up;
    up.y = 1.0f;

    gluLookAt(
        eye.x, eye.y, eye.z,
        center.x, center.y, center.z,
        up.x, up.y, up.z );
}

void OpenGLWrapperLegacyConcrete::clearFrame()
{
    glClear( GL_COLOR_BUFFER_BIT );
}

void OpenGLWrapperLegacyConcrete::renderFrame()
{

}

void OpenGLWrapperLegacyConcrete::customFrameSteps()
{
    for( const auto& fs: m_customSteps )
    {
        fs.second();
    }
}

void OpenGLWrapperLegacyConcrete::updateBuffers()
{
    m_sdl2w->getMainWindow()->updateScreenBuffers();
}

void OpenGLWrapperLegacyConcrete::addCustomFrameStep(
    const std::function<void()>& callback,
    Cunt id )
{
    m_customSteps[id] = callback;
}

void OpenGLWrapperLegacyConcrete::removeCustomFrameStep( Cunt id )
{
    m_customSteps.erase( id );
}

const bool OpenGLWrapperLegacyConcrete::customFrameStepExists( Cunt id ) const
{
    return m_customSteps.find( id ) != m_customSteps.end();
}

void OpenGLWrapperLegacyConcrete::cleanup()
{
    if( m_oglContext )
    {
        SDL_GL_DeleteContext( m_oglContext );
        m_oglContext = nullptr; // This is basically void* !
    }
    else
    {
        CUL::Assert::simple( false, "Cannot destroy m_oglContext. It was destroyed elsewhere or was not created." );
    }
}

OpenGLWrapperLegacyConcrete::~OpenGLWrapperLegacyConcrete()
{
    if( false == m_customSteps.empty() )
    {
        m_customSteps.clear();
    }
}