#include "window.hpp"
#include "color.cpp"
#include "mandelbrot.hpp"

#include <iostream>

#include <SDL2/SDL.h>

Window::Window(/* args */)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        // return 1;
    }

    this->win = SDL_CreateWindow("Hello World!", 100, 100, length, height, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        // return 1;
    }

    this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        SDL_DestroyWindow(this->win);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        // return 1;
    }
}

Window::~Window()
{
    SDL_DestroyRenderer(this->ren);
    SDL_DestroyWindow(this->win);
    SDL_Quit();
}

void Window::renderSet(const Mandelbrot &m)
{

    SDL_RenderClear(ren);

    // help with https://www.codingame.com/playgrounds/2358/how-to-plot-the-mandelbrot-set/adding-some-colors
    // std::unordered_map<int, int> histogram;
    // std::unordered_map<std::pair<int, int>, float, hash> values;

    float n;
    // int max_out = 0;

    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < length; ++col)
        {
            n = m.mandelbrot(col, row);

            // if (n == nb_ite)
            //     max_out++;
            // else
            //     histogram[floor(n)] += 1;

            // values[std::pair<int, int>(row, col)] = n;
            hsv source = hsv((n / m.getIteration()) * 360, 1.f, n < m.getIteration() ? 1.f : 0.f);
            rgb dest = hsv2rgb(source);

            SDL_SetRenderDrawColor(this->ren, dest.r * 255, dest.g * 255, dest.b * 255, 0);
            SDL_RenderDrawPoint(this->ren, col, row);
        }
    }

    // float total = (length * height) - max_out;
    // std::vector<float> hues;
    // float h = 0.f;

    // for (int i = 0; i < nb_ite; i++)
    // {
    //     if (histogram.find(i) != histogram.end())
    //         h += (histogram[i] / total);
    //     hues.push_back(h);
    // }
    // hues.push_back(h);

    // float interpolation, linear_percent;
    // double m, integral;

    // for (int row = 0; row < height; ++row)
    // {
    //     for (int col = 0; col < length; ++col)
    //     {
    //         m = values[std::pair<int, int>(row, col)];
    //         // std::cout << m << std::endl;
    //         linear_percent = modf(m, &integral);
    //         interpolation = hues[floor(m)] * (1 - linear_percent) + hues[ceil(m)] * linear_percent;

    //         hsv source = hsv(interpolation * 360, 1.f, n < nb_ite ? 1.f : 0.f);
    //         rgb dest = hsv2rgb(source);

    //         SDL_SetRenderDrawColor(renderer, (Uint8)(dest.r * 255), (Uint8)(dest.g * 255), (Uint8)(dest.b * 255), 0);
    //         SDL_RenderDrawPoint(renderer, col, row);
    //     }
    // }
    SDL_RenderPresent(ren);
}

int Window::getLength() const
{
    return this->length;
}

int Window::getHeight() const
{
    return this->height;
}
