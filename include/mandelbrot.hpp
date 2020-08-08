#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

class Mandelbrot
{
private:
    double base_minx = -2.4f;
    double base_maxx = 1.f;

    double base_miny = -1.f;
    double base_maxy = 1.f;

    double minx;
    double maxx;

    double miny;
    double maxy;

    double zoomStrength = 2.f;
    int zoomState = 0;

    int length;
    int height;

    int nb_ite = 100    ;

public:
    Mandelbrot(int length, int height);
    ~Mandelbrot();

    void zoomIn(int, int);
    void zoomOut(int, int);
    double mandelbrot(int, int) const;

    int getIteration() const;
    void setIteration(int);
};

#endif