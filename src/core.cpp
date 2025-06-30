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
        if( SDL_CreateWindowAndRenderer( "SDL3 Tutorial: Textures and Extension Libraries", window.kScreenWidth, window.kScreenHeight, 0, &gWindow, &gRenderer ) == false)
        {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success.val = 0;
        }
    }

    return success;
}

struct flag Core::loadMedia()
{
    struct flag success = { 1 };

    //Load splash image
    std::string imagePath{ "images/cloud.png" };
    if( png.loadFromFile( imagePath.c_str(), gRenderer ) == false )
    {
        SDL_Log( "Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError() );
        success.val = 0;
    }

    return success;
}

void Core::close()
{
    png.destroy();

    SDL_DestroyRenderer( gRenderer );
    gRenderer = nullptr;
    //Clean up surface
    
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

