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
        bool loadFromFile( std::string path, SDL_Renderer* gRenderer );

        //Cleans up texture
        void destroy();

        //Draws texture
        void render( float x, float y, SDL_Renderer* gRenderer );
        
        Texture( const Texture& ) = delete;

        //Remove copy assignment
        Texture& operator=( const Texture& ) = delete;

        //Remove move constructor
        Texture( Texture&& ) = delete;

        //Remove move assignment
        Texture& operator=( Texture&& ) = delete;

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
