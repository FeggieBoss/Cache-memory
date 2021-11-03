#include "element.hpp"

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

double get_rng_double() {
    int x = rng(), y = rng();
    return (double)x / (abs(y)+1);
}

element::element() {
    x = y = ax = ay = vx = vy = a = b = 0;
}

element::element(double* mas) {
    x  = mas[0];
    y  = mas[1];
    ax = mas[2];
    ay = mas[3];
    vx = mas[4];
    vy = mas[5];
    a  = mas[6];
    b  = mas[7];
}

element element::get_rng_element() {
    element e;

    e.x = get_rng_double();
    e.y = get_rng_double();
    e.ax = get_rng_double();
    e.ay = get_rng_double();
    e.vx = get_rng_double();
    e.vy = get_rng_double();
    e.a = get_rng_double();
    e.b = get_rng_double();
        
    return e;
}

void element::write_element(double* mas) {
    mas[0] = x;
    mas[1] = y;
    mas[2] = ax;
    mas[3] = ay;
    mas[4] = vx;
    mas[5] = vy;
    mas[6] = a;
    mas[7] = b;
}