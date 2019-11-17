#include "MatrixStack.hpp"
#include "libopenglwrapperlegacy/OpenGLWrapperLegacy.hpp"
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "CUL/Math/Axis.hpp"
#include "CUL/GenericUtils/ConsoleUtilities.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Graphics/Rect2D.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

using SDLWrap = CUL::GUTILS::DumbPtr<SDL2W::ISDL2Wrapper>;
using Color = CUL::Graphics::ColorS;
using WinEventType = SDL2W::WindowEvent::Type;
using ShaderFile = CUL::GUTILS::DumbPtr<CUL::FS::IFile>;
template <typename TYPE> using DumbPtr = CUL::GUTILS::DumbPtr<TYPE>;
using FF = CUL::FS::FileFactory;
using Rect = CUL::Graphics::Rect3Di;
using String = CUL::MyString;
using Vector3Di = SDL2W::Vector3Di;
using Vector3Du = SDL2W::Vector3Du;
using WindowsSize = SDL2W::WindowSize;

OGLWL::IOpenGLwrapperLegacy* g_oglw = nullptr;
SDL2W::ISDL2Wrapper* g_sdlw = nullptr;;
OGLWL::MatrixStack matrixStack;
Color red( 1.0f, 0.0f, 0.0f, 1.0f );
Color blue( 0.0f, 0.0f, 1.0f, 1.0f );
Color black;
GLfloat angle = 0.0f;
ShaderFile vertexShaderFile;
ShaderFile fragmentShaderFile;

void renderScene( void );
void onKeyBoardEvent( const SDL2W::IKey& key );
void onWindowEvent( const WinEventType type );
void closeApp();

struct Pos
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

void assert( const bool statement, const String& message )
{
    CUL::Assert::simple(
        statement,
        message );
}

void setPerspectiveProjection( const Rect& viewPortRect, const double fovAngle = 90.0 );
void resetTransformations();
void frame();
void drawTriangle( const Color& color );
void drawQuad( const Color& color );

int main( int argc, char** argv )
{
    auto& argsInstance = CUL::GUTILS::ConsoleUtilities::getInstance();
    argsInstance.setArgs( argc, argv );

    SDL2W::WindowData wd;
    wd.size.setSize( 640, 480 );
    wd.pos.setXYZ( 256, 256, 0 );
    wd.name = "Test";

    SDLWrap sdlWrap = SDL2W::createSDL2Wrapper( wd );
    g_sdlw = sdlWrap;
    sdlWrap->registerWindowEventCallback( onWindowEvent );
    sdlWrap->registerKeyboardEventCallback( onKeyBoardEvent );

    g_oglw = OGLWL::createWrapper( sdlWrap );

    auto& size = sdlWrap->getMainWindow()->getSize();
    auto w = static_cast<GLsizei>( size.getWidth() );
    auto h = static_cast<GLsizei>( size.getHeight() );
    Rect rect;
    rect.width = w;
    rect.height = h;

    g_oglw->addCustomFrameStep( frame, 0 );
    g_oglw->start();
    sdlWrap->runEventLoop();

    return 0;
}

void setPerspectiveProjection( const Rect& viewPortRect, const double fovAngle )
{
    GLfloat ratio = (GLfloat) ( viewPortRect.width * 1.0 / viewPortRect.height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport( viewPortRect.x, viewPortRect.y, viewPortRect.width, viewPortRect.height );
    gluPerspective( fovAngle, ratio, 0, 20 );
}

void frame()
{
    renderScene();
}

void renderScene()
{
    glPushMatrix();
        glRotatef( angle, 0.0f, 0.0f, 1.0f );
        glTranslatef( 2.0f, 0.0f, 4.0f );
        drawQuad( red );
        glRotatef( 180.0f, 0.0f, 0.0f, 1.0f );
        drawTriangle( blue );
    glPopMatrix();
    angle += 0.1f;
}

void resetTransformations()
{
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

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

void drawTriangle( const Color& color )
{
    glColor4f( color.getRF(), color.getGF(), color.getBF(), color.getAF() );
    glBegin( GL_TRIANGLES );
        glVertex3f( 2.0f, -2.0f, 0.0f );
        glVertex3f( -2.0f, -2.0f, 0.0f );
        glVertex3f( -2.0f, 2.0f, 0.0f );
    glEnd();
}

void drawQuad( const Color& color )
{
    glColor4f( color.getRF(), color.getGF(), color.getBF(), color.getAF() );
    glBegin( GL_QUADS );
        glVertex3f(  2.0f, -2.0f, 0.0f );
        glVertex3f( -2.0f, -2.0f, 0.0f );
        glVertex3f( -2.0f,  2.0f, 0.0f );
        glVertex3f(  2.0f,  2.0f, 0.0f );
    glEnd();
}

void onKeyBoardEvent( const SDL2W::IKey& key )
{
    if( key.getKeyName() == "q" || key.getKeyName() == "Q" )
    {
        closeApp();
    }
}

void onWindowEvent( const WinEventType type )
{
    if( WinEventType::CLOSE == type )
    {
        closeApp();
    }
}

void closeApp()
{
    g_oglw->signalStop();
    delete g_oglw;
    g_oglw = nullptr;
    g_sdlw->stopEventLoop();
}