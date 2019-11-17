#include "libopenglwrapperlegacy/OpenGLWrapperLegacy.hpp"
#include "OpenGLWrapperLegacyConcrete.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

OGLWL::IOpenGLwrapperLegacy* OGLWL::createWrapper( SDL2W::ISDL2Wrapper* sdl2w )
{
    CUL::Assert::simple( nullptr != sdl2w );
    auto result = new OpenGLWrapperLegacyConcrete( sdl2w );
    return result;
}