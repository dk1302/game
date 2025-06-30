#include "core.h"

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
    if( gImage = SDL_LoadBMP( imagePath.c_str() ); gImage == nullptr )
    {
        SDL_Log( "Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError() );
        success.val = 0;
    }

    return success;
}

void Core::close()
{
    //Clean up surface
    SDL_DestroySurface( gImage );
    gImage = nullptr;
    
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    gScreenSurface = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

