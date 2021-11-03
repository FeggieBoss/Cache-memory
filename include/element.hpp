#include <random>
#include <chrono>

double get_rng_double();

struct element
{
    double x, y, ax, ay, vx, vy, a, b;

    element();

    element(double* mas);

    element get_rng_element();

    void write_element(double* mas);
};