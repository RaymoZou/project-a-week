#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

// ./main.exe image.png
//
char *file_path;
SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char **argv) {
    // TODO: check for init failures
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    
    if (argc == 2) {
        file_path = argv[1];
        SDL_Log("file location: %s", file_path);
    } else {
        SDL_Log("invalid argument input\n");
    };

    window = SDL_CreateWindow("Animator", 0, 0, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

    return 0;
};
