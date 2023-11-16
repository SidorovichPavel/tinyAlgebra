#include <tinyalgebralib/math/Vector.hpp>

int main(int argc, char* args[]) {

    ta::Vector<float, 2> vec(1.f);
    ta::Vector<float, 3> v(vec, 10.f);
    v += ta::Vector<float, 3>(1.f);

    return 0;
}