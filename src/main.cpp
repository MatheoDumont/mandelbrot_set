#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

int minx = 0;
int miny = 0;
int maxx = 640;
int maxy = 480;

int nb_ite = 1000;

int mandelbrot(int, int);
void set_pixel(SDL_Surface *, int, int, Uint32);
SDL_Surface *computeSurface();

int main(int argc, char *argv[])
{
    SDL_Window *win;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    win = SDL_CreateWindow("Hello World!", 100, 100, maxx, maxy, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Event e;
    bool change = true;
    SDL_Texture *tex = nullptr;
    SDL_Surface *surface = nullptr;

    while (1)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
            if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN)
            {
                change = true;
            }
        }

        if (change)
        {
            surface = computeSurface();
            tex = SDL_CreateTextureFromSurface(ren, surface);

            if (tex == nullptr)
            {
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(win);
                std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
                SDL_Quit();
                return 1;
            }

            SDL_FreeSurface(surface);
            //First clear the renderer
            SDL_RenderClear(ren);
            //Draw the texture
            SDL_RenderCopy(ren, tex, NULL, NULL);
            //Update the screen
            SDL_RenderPresent(ren);

            change = false;
        }
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    // https://stackoverflow.com/questions/20070155/how-to-set-a-pixel-in-a-sdl-surface
    Uint32 *target_pixel = (Uint32 *)surface->pixels + y * surface->pitch +
                           x * sizeof(*target_pixel);
    *target_pixel = pixel;
}

SDL_Surface *computeSurface()
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0, maxx, maxy, 32, 0, 0, 0, 0);
    int n;
    Uint32 pixel;
    for (int row = 0; row < maxx; ++row)
    {
        for (int col = 0; col < maxy; ++col)
        {
            n = mandelbrot(row, col);
            // TODO pixel = ... (linear, exponential function for the color)
            pixel = exp(n);
            set_pixel(surface, row, col, pixel);
        }
    }
}

int mandelbrot(int x, int y)
{
    float c_x, c_y, realx, imy;
    // on reduit les points dans l'espace de la serie de mandelbrot
    c_x = (x / maxx) * (maxx - minx) + minx;
    c_y = (y / maxy) * (maxy - miny) + miny;

    realx = 0.f;
    imy = 0.f;

    int i = 0;
    // tant que les valeurs sont inferieur a un cercle de radius de 2
    while (realx * imy <= 4 && i < nb_ite)
    {
        realx = (realx * realx) - (imy * imy) + c_x;
        imy = (2 * realx * imy) + c_y;
        ++i;
    }

    return i;
}