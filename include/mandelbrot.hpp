#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

class Mandelbrot
{
private:
    float base_minx = -2.4f;
    float base_maxx = 1.f;

    float base_miny = -1.f;
    float base_maxy = 1.f;

    float minx;
    float maxx;

    float miny;
    float maxy;

    float zoomStrength = 1.1f;
    int zoomState = 0;

    int length;
    int height;

    int nb_ite = 100;

public:
    Mandelbrot(int length, int height);
    ~Mandelbrot();

    void zoomIn(int, int);
    void zoomOut(int, int);
    float mandelbrot(int, int) const;

    int getIteration() const;
    void setIteration(int);
};

#endif