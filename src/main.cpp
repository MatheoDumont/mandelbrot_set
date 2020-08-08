#define SDL_MAIN_HANDLED

#include <unistd.h>
#include <SDL2/SDL.h>

#include "mandelbrot.hpp"
#include "window.hpp"

void loop(Window &w, Mandelbrot &m)
{
    SDL_Event e;
    bool change = true;
    bool leave = false;

    while (!leave)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN)
                leave = true;
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                // SDL_GetGlobalMouseState(&x, &y);
                // SDL_GetRelativeMouseState(&x, &y);

                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    m.zoomIn(x, y);
                }
                else if (e.button.button == SDL_BUTTON_RIGHT)
                {
                    m.zoomOut(x, y);
                }

                change = true;
            }
        }

        if (change)
        {
            w.renderSet(m);
            change = false;
        }
    }
}

void linear_print(Window &w, Mandelbrot &m)
{

    // int tab[] = {1, 5, 10, 25, 50, 75, 100, 125};

    // for (int i = 0; i < sizeof(tab) / sizeof(int); i++)
    for (int i = 0; i < 200; i += 10)
    {
        m.setIteration(i);
        w.renderSet(m);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    Window w;
    Mandelbrot m(w.getLength(), w.getHeight());

    // linear_print(w, m);
    loop(w, m);

    return EXIT_SUCCESS;
}
