#include <iostream>

int main(int argc, char const* argv[]) {
    unsigned int* x_base;
    unsigned int* x_16 = x_base + 16;
    *x_16 = 1;
    unsigned int v_16 = *x_16;

    std::cout << v_16 << std::endl;
    return 0;
}
