#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "texture.h"
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

        SDL_Renderer* gRenderer{ nullptr };
            
        //The surface contained by the window
        SDL_Surface* gScreenSurface{ nullptr };

        //The image we will load and show on the screen
        SDL_Surface* gImage{ nullptr };
        
        Texture png;
};
