#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include "mandelbrot.hpp"

class Window
{
private:
    /* data */
    int length = 1280;
    int height = 720;

    SDL_Window *win;
    SDL_Renderer *ren;

public:
    Window(/* args */);
    ~Window();

    void renderSet(const Mandelbrot &mandelbrot);

    int getLength() const;
    int getHeight() const;
};

#endif