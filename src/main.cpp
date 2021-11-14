#include "f.hpp"

void $main() {
    element arr[n];
    for (size_t i = 0; i < n; ++i) {
        arr[i] = arr[i].get_rng_element();
    }

    auto c_arr = cache_arr(arr);
    double asqr = get_rng_double();
    f(c_arr, n, asqr);
    c_arr.print_log();
}

int main()
{
    $main();
    return 0;
}