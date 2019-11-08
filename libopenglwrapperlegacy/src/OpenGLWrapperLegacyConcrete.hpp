#pragma once

#include "libopenglwrapperlegacy/IOpenGLWrapperLegacy.hpp"
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/GenericUtils/LckPrim.hpp"

NAMESPACE_BEGIN( OGLWL )

class OpenGLWrapperLegacyConcrete final:
    public IOpenGLwrapperLegacy
{
public:
    explicit OpenGLWrapperLegacyConcrete( SDL2W::ISDL2Wrapper* sdl2w );
    

    void start() override;
    void signalStop() override;

protected:
private:
    OpenGLWrapperLegacyConcrete() = delete;
    OpenGLWrapperLegacyConcrete( const OpenGLWrapperLegacyConcrete& arg ) = delete;
    OpenGLWrapperLegacyConcrete& operator=( const OpenGLWrapperLegacyConcrete& rhv ) = delete;
    ~OpenGLWrapperLegacyConcrete();

    void mainLoop();
    void initialize();

    CUL::GUTILS::LckBool m_runMainLoop = true;
    SDL2W::ISDL2Wrapper* m_sdl2w = nullptr;
    std::thread m_renderingLoopThread;

};

NAMESPACE_END( OGLWL )