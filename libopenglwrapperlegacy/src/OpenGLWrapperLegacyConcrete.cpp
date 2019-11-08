#include "OpenGLWrapperLegacyConcrete.hpp"

using namespace OGLWL;


/*
Why not move SDL window create to the guts of OGLWL?
In the future, I want to build a engine which can change
its renderer on the fly.
*/
OpenGLWrapperLegacyConcrete::OpenGLWrapperLegacyConcrete(
    SDL2W::ISDL2Wrapper* sdl2w ):
    m_sdl2w( sdl2w )
{
}

OpenGLWrapperLegacyConcrete::~OpenGLWrapperLegacyConcrete()
{

}

void OpenGLWrapperLegacyConcrete::start()
{
    m_renderingLoopThread = std::thread( &OpenGLWrapperLegacyConcrete::mainLoop, this );
}

void OpenGLWrapperLegacyConcrete::signalStop()
{
    m_runMainLoop = false;
}

void OpenGLWrapperLegacyConcrete::mainLoop()
{
    initialize();
    while( m_runMainLoop )
    {

    }
    delete this;
}

void OpenGLWrapperLegacyConcrete::initialize()
{
}