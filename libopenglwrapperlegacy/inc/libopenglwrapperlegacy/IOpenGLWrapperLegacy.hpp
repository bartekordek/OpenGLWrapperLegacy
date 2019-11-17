#pragma once

#include "libopenglwrapperlegacy/Import.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( OGLWL )

using Cunt = const unsigned int;

class OGLWLAPI IOpenGLwrapperLegacy
{
public:
    enum class ProjectionType: short
    {
        ORTHORGRAPHIC = 0,
        PERSPECTIVE
    };

    IOpenGLwrapperLegacy();
    virtual ~IOpenGLwrapperLegacy();

    virtual void start() = 0;
    virtual void signalStop() = 0;

    virtual void addCustomFrameStep( const std::function<void()>& callback, Cunt id ) = 0;
    virtual void removeCustomFrameStep( Cunt id ) = 0;
    virtual const bool customFrameStepExists( Cunt id ) const = 0;

protected:
private:
    IOpenGLwrapperLegacy( const IOpenGLwrapperLegacy& arg ) = delete;
    IOpenGLwrapperLegacy& operator=( const IOpenGLwrapperLegacy& rhv ) = delete;

};

NAMESPACE_END( OGLWL )