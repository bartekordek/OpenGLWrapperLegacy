#pragma once

#include "libopenglwrapperlegacy/Import.hpp"

NAMESPACE_BEGIN( OGLWL )

class OGLWLAPI IOpenGLwrapperLegacy
{
public:
    IOpenGLwrapperLegacy();
    virtual ~IOpenGLwrapperLegacy();

    virtual void start() = 0;
    virtual void signalStop() = 0;

protected:
private:
    IOpenGLwrapperLegacy( const IOpenGLwrapperLegacy& arg ) = delete;
    IOpenGLwrapperLegacy& operator=( const IOpenGLwrapperLegacy& rhv ) = delete;

};

NAMESPACE_END( OGLWL )