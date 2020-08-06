#include "mandelbrot.hpp"
#include <math.h>

Mandelbrot::Mandelbrot(int length, int height)
    : length(length), height(height), minx(base_minx), maxx(base_maxx), miny(base_miny), maxy(base_maxy)
{
}
Mandelbrot::~Mandelbrot() {}

void Mandelbrot::zoomIn(int x, int y)
{
    float pointx, pointy;
    // passer dans le repere du plan dans lequel on travail
    pointx = (x / (float)length) * (maxx - minx) + minx;
    pointy = (y / (float)height) * (maxy - miny) + miny;

    minx = pointx + abs(minx / zoomStrength);
    maxx = pointx - abs(maxx / zoomStrength);

    miny = pointy + abs(miny / zoomStrength);
    maxy = pointy - abs(maxy / zoomStrength);

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
        float pointx, pointy;
        pointx = (x / (float)length) * (maxx - minx) + minx;
        pointy = (y / (float)height) * (maxy - miny) + miny;

        minx = pointx - abs(minx / zoomStrength);
        maxx = pointx + abs(maxx / zoomStrength);

        miny = pointy - abs(miny / zoomStrength);
        maxy = pointy + abs(maxy / zoomStrength);
    }
}

float Mandelbrot::mandelbrot(int x, int y) const
{
    float c_x, c_y, realx, imy, tmpx;
    // on reduit les points dans l'espace de la serie de mandelbrot
    c_x = (x / (float)length) * (maxx - minx) + minx;
    c_y = (y / (float)height) * (maxy - miny) + miny;

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
