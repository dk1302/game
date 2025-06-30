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

                SDL_SetRenderDrawColor( core.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( core.gRenderer );
            
                //Render image on screen
                core.png.render( 0.f, 0.f, core.gRenderer );

                //Update screen
                SDL_RenderPresent( core.gRenderer );            } 
        }
    }

    //Clean up
    core.close();

    return exitCode;
}
