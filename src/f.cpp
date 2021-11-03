#include "f.hpp"

void f(cache_arr& arr, int n, double asqr) {
    for (int i = 0; i < n; ++i) {
       //arr[i].x += arr[i].vx * asqr + 0.5 * arr[i].ax * asqr * asqr;
       double arr_i_vx = arr.read(i, VX);
       double arr_i_ax = arr.read(i, AX);
       double arr_i_x = arr.read(i, X);
       arr.write(i, X, arr_i_x + arr_i_vx * asqr + 0.5 * arr_i_ax * asqr * asqr);
    }

    for (int i = 0; i < n; ++i) {
        //arr[i].y += arr[i].vy * asqr + 0.5 * arr[i].ay * asqr * asqr;
        double arr_i_vy = arr.read(i, VY);
        double arr_i_ay = arr.read(i, AY);
        double arr_i_y = arr.read(i, Y);
        arr.write(i, Y, arr_i_y + arr_i_vy * asqr + 0.5 * arr_i_ay * asqr * asqr);
    }
}