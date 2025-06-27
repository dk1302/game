/*This source code copyrighted by Lazy Foo' Productions 2004-2025
and may not be redistributed without written permission.*/

/* Headers */
//Using SDL and STL string
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include <string>

struct flag {
    unsigned int val : 1;
};

struct windowSize {
    unsigned int kScreenWidth : 12;
    unsigned int kScreenHeight : 12;
};

class Core {
    private:
        struct windowSize window = { 640, 480 };
    public:
        struct flag init();
        struct flag loadMedia();
        void close();

        SDL_Window* gWindow{ nullptr };
            
        //The surface contained by the window
        SDL_Surface* gScreenSurface{ nullptr };

        //The image we will load and show on the screen
        SDL_Surface* gHelloWorld{ nullptr };

};

/* Function Implementations */
struct flag Core::init()
{
    struct flag success = { 1 };

    //Initialize SDL
    if( !SDL_Init( SDL_INIT_VIDEO ) )
    {
        SDL_Log( "SDL could not initialize! SDL error: %s\n", SDL_GetError() );
        success.val = 0;
    }
    else
    {
        //Create window
        if( gWindow = SDL_CreateWindow( "SDL3 Tutorial: Hello SDL3", window.kScreenWidth, window.kScreenHeight, 0 ); gWindow == nullptr )
        {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success.val = 0;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

struct flag Core::loadMedia()
{
    struct flag success = { 1 };

    //Load splash image
    std::string imagePath{ "images/image.bmp" };
    if( gHelloWorld = SDL_LoadBMP( imagePath.c_str() ); gHelloWorld == nullptr )
    {
        SDL_Log( "Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError() );
        success.val = 0;
    }

    return success;
}

void Core::close()
{
    //Clean up surface
    SDL_DestroySurface( gHelloWorld );
    gHelloWorld = nullptr;
    
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    gScreenSurface = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Final exit code
    int exitCode{ 0 };
    Core core;

    //Initialize
    if( !core.init().val )
    {
        SDL_Log( "Unable to initialize program!\n" );
        exitCode = 1;
    }
    else
    {
        //Load media
        if( !core.loadMedia().val )
        {
            SDL_Log( "Unable to load media!\n" );
            exitCode = 2;
        }
        else
        {
            //The quit flag
            bool quit{ false };

            //The event data
            SDL_Event e;
            SDL_zero( e );
            
            //The main loop
            while( quit == false )
            {
                //Get event data
                while( SDL_PollEvent( &e ) )
                {
                    //If event is quit type
                    if( e.type == SDL_EVENT_QUIT )
                    {
                        //End the main loop
                        quit = true;
                    }
                }

                //Fill the surface white
                SDL_FillSurfaceRect( core.gScreenSurface, nullptr, SDL_MapSurfaceRGB( core.gScreenSurface, 0xFF, 0xFF, 0xFF ) );
            
                //Render image on screen
                SDL_BlitSurface( core.gHelloWorld, nullptr, core.gScreenSurface, nullptr );

                //Update the surface
                SDL_UpdateWindowSurface( core.gWindow );
            } 
        }
    }

    //Clean up
    core.close();

    return exitCode;
}
