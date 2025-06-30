/*This source code copyrighted by Lazy Foo' Productions 2004-2025
and may not be redistributed without written permission.*/

/* Headers */
//Using SDL and STL string
#include "core.h"

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
                SDL_BlitSurface( core.gImage, nullptr, core.gScreenSurface, nullptr );

                //Update the surface
                SDL_UpdateWindowSurface( core.gWindow );
            } 
        }
    }

    //Clean up
    core.close();

    return exitCode;
}
