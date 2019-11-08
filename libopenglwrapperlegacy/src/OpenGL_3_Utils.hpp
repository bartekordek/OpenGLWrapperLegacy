#pragma once

#include "libopenglwrapperlegacy/Import.hpp"

#include "CUL/Graphics/Color.hpp"
#include "CUL/Graphics/Rect2D.hpp"
#include "CUL/Graphics/Pos2D.hpp"
#include "CUL/Graphics/Size2D.hpp"
#include "CUL/Math/Angle.hpp"
#include "CUL/MyString.hpp"

#include "IMPORT_glew.hpp"

NAMESPACE_BEGIN( OGLWL )

using CDouble = const double;
using Angle = CUL::Math::Angle;
using Cunt = const unsigned int;
using String = CUL::MyString;

class UTILS
{
public:
    using DispRect = CUL::Graphics::Rect2D<unsigned int>;
    
    using ColorS = CUL::Graphics::ColorS;
    using ColorE = CUL::Graphics::ColorE;
    struct ViewPortRect
    {
        CUL::Graphics::Pos2Di pos;
        CUL::Graphics::Size2Du size;
    };
    static void resetMatrixToIdentity( const GLenum matrix );
    static void setViewPort( const ViewPortRect& rect );

    static const GLuint toGluint( Cunt value );

    static String initContextVersion( Cunt major, Cunt minor );
    static void setProjectionAndModelToIdentity();
    static void clearColorAndDepthBuffer();
    static void createQuad();
    static void clearColorTo( const ColorS color );

    static void listExtensions();

protected:
private:
    UTILS() = delete;
    UTILS( const UTILS& arg ) = delete;
    UTILS& operator=( const UTILS& rhv ) = delete;
    ~UTILS() = delete;

};

NAMESPACE_END( OGLWL )