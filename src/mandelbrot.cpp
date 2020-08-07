#include "mandelbrot.hpp"
#include <math.h>
#include <iostream>

Mandelbrot::Mandelbrot(int length, int height)
    : length(length), height(height), minx(base_minx), maxx(base_maxx), miny(base_miny), maxy(base_maxy)
{
}
Mandelbrot::~Mandelbrot() {}

void Mandelbrot::zoomIn(int x, int y)
{
    double pointx, pointy;
    // std::cout << " x :" << x << " y : " << y << std::endl;
    // passer dans le repere du plan dans lequel on travail

    // std::cout << "minx :" << minx << " maxx : " << maxx << " miny : " << miny << " maxy : " << maxy << std::endl;

    pointx = (x / (double)length) * (maxx - minx) + minx;
    pointy = (y / (double)height) * (maxy - miny) + miny;

    // std::cout << "Dans le repere,x : " << pointx << " y : " << pointy << std::endl;

    minx += (pointx - minx) / zoomStrength;
    maxx -= (maxx - pointx) / zoomStrength;

    miny += (pointy - miny) / zoomStrength;
    maxy -= (maxy - pointy) / zoomStrength;

    // std::cout << "minx :" << minx << " maxx : " << maxx << " miny : " << miny << " maxy : " << maxy << std::endl;

    zoomState++;
}

void Mandelbrot::zoomOut(int x, int y)
{
    if (zoomState == 0 || zoomState == 1)
    {
        zoomState = 0;
        minx = base_minx;
        miny = base_miny;

        maxx = base_maxx;
        maxy = base_maxy;
    }
    else
    {
        zoomState--;
        double pointx, pointy;

        pointx = (x / (double)length) * (maxx - minx) + minx;
        pointy = (y / (double)height) * (maxy - miny) + miny;

        minx -= (pointx - minx) / zoomStrength;
        maxx += (maxx - pointx) / zoomStrength;

        miny -= (pointy - miny) / zoomStrength;
        maxy += (maxy - pointy) / zoomStrength;
    }
}

double Mandelbrot::mandelbrot(int x, int y) const
{
    double c_x, c_y, realx, imy, tmpx;
    // on reduit les points dans l'espace de la serie de mandelbrot
    c_x = (x / (double)length) * (maxx - minx) + minx;
    c_y = (y / (double)height) * (maxy - miny) + miny;

    realx = 0.f;
    imy = 0.f;

    int i = 0;
    // tant que les valeurs sont inferieur a un cercle de radius de 2
    while (sqrt((realx * realx) + (imy * imy)) <= 2 && i < nb_ite)
    {
        tmpx = (realx * realx) - (imy * imy) + c_x;
        imy = (2 * realx * imy) + c_y;
        realx = tmpx;
        ++i;
    }

    // if (i == nb_ite)
    //     return nb_ite;

    // double absolute = sqrt((realx * realx) + (imy * imy));
    // double ret = i + 1 - log(log2(absolute));
    // if (!isfinite(absolute) || !isfinite(ret))
    //     // std::cout << "cx " << c_x << " cy " << c_y << " realx " << realx << " imy " << imy << " i " << i << " abs " << absolute << " ret " << ret << std::endl;
    //     return 0;

    return i;
}

int Mandelbrot::getIteration() const
{
    return this->nb_ite;
}

void Mandelbrot::setIteration(int ite)
{
    this->nb_ite = ite;
}
