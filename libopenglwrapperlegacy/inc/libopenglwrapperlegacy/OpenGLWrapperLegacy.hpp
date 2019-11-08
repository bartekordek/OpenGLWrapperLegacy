#include "libopenglwrapperlegacy/IOpenGLWrapperLegacy.hpp"
#include "SDL2Wrapper/ISDL2Wrapper.hpp"

NAMESPACE_BEGIN( OGLWL )

OGLWLAPI IOpenGLwrapperLegacy* createWrapper( SDL2W::ISDL2Wrapper* sdl2w );

NAMESPACE_END( OGLWL )