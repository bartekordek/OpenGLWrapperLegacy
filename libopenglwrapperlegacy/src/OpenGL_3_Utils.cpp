#include "OpenGL_3_Utils.hpp"

#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "IMPORT_SDL_opengl.hpp"

#include "IMPORT_freeglut.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"

using namespace OGLWL;

void UTILS::setViewPort( const ViewPortRect& rect )
{
    glViewport( 
        static_cast<GLint>( rect.pos.getX() ),
        static_cast<GLint>( rect.pos.getY() ),
        static_cast<GLsizei>( rect.size.getWidth() ),
        static_cast<GLsizei>( rect.size.getHeight() ) );
}

void UTILS::setProjectionAndModelToIdentity()
{
    resetMatrixToIdentity( GL_PROJECTION );
    resetMatrixToIdentity( GL_MODELVIEW );
}

String UTILS::initContextVersion( Cunt major, Cunt minor )
{
    String contextInfo;
    //glutInitContextVersion( static_cast<int>( major ), static_cast<int>( minor ) );
    /*
    Context version can be only set after context creation.
    I.e. SDL: SDL_GL_DeleteContext call.
    */
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, static_cast<int>( major ) );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, static_cast<int>( minor ) );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    // Possible values:
    //typedef enum
    //{
    //    SDL_GL_CONTEXT_PROFILE_CORE = 0x0001,
    //    SDL_GL_CONTEXT_PROFILE_COMPATIBILITY = 0x0002,
    //    SDL_GL_CONTEXT_PROFILE_ES = 0x0004 /**< GLX_CONTEXT_ES2_PROFILE_BIT_EXT */
    //} SDL_GLprofile;
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG );
    contextInfo = glGetString( GL_VERSION );

    if( major >= 3 )
    {
        auto error = glewInit();
        CUL::Assert::simple(
            GLEW_OK == error,
            "GLEW error: " +
            String( reinterpret_cast<const char*>( glewGetErrorString( error ) ) +
                contextInfo ) );
    }
    return contextInfo;
}

void UTILS::resetMatrixToIdentity( const GLenum matrix )
{
    glMatrixMode( matrix );
    glLoadIdentity();
}

void UTILS::clearColorAndDepthBuffer()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void UTILS::createQuad()
{
    glBegin( GL_QUADS );
        glColor3f( 1.f, 1.f, 1.f );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f( 0.5f, -0.5f );
        glVertex2f( 0.5f, 0.5f );
        glVertex2f( -0.5f, 0.5f );
    glEnd();
}

void UTILS::clearColorTo( const ColorS color )
{
    glClearColor(
        static_cast<GLclampf>( color.getRF() ),
        static_cast<GLclampf>( color.getGF() ),
        static_cast<GLclampf>( color.getBF() ),
        static_cast<GLclampf>( color.getAF() ) );
}

template <typename Out>
void split( const std::string &s, char delim, Out result )
{
    std::istringstream iss( s );
    std::string item;
    while( std::getline( iss, item, delim ) )
    {
        *result++ = item;
    }
}

std::vector<std::string> split( const std::string &s, char delim );

void UTILS::listExtensions()
{
    GLint extensionsCount = 0;
    glGetIntegerv( GL_NUM_EXTENSIONS, &extensionsCount );
    const GLubyte* extensions = glGetString( GL_EXTENSIONS );
    String wat = static_cast<const unsigned char*>( extensions );
    std::vector<std::string> extensionsVec = split( wat.string(), ' ' );
    for( const auto& extension: extensionsVec )
    {
        std::cout << extension << "\n";
    }
}

std::vector<std::string> split( const std::string &s, char delim )
{
    std::vector<std::string> elems;
    split( s, delim, std::back_inserter( elems ) );
    return elems;
}

const GLuint UTILS::toGluint( Cunt value )
{
    return static_cast<GLuint>( value );
}