#include "SDL3_image/SDL_image.h"
#include <string>

class Texture
{
    public:
        //Initializes texture variables
        Texture();

        //Cleans up texture variables
        ~Texture();

        //Loads texture from disk
        bool loadFromFile( std::string path );

        //Cleans up texture
        void destroy();

        //Draws texture
        void render( float x, float y );

        //Gets texture attributes
        int getWidth();
        int getHeight();
        bool isLoaded();

    private:
        //Contains texture data
        SDL_Texture* mTexture;

        //Texture dimensions
        int mWidth;
        int mHeight;
};
