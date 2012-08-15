#include "Cell.h"

#ifdef DEBUG

#include "Coords.h"
#include <stdint.h>
#include <iostream>

using namespace Chess;

int main() {
    Coords<int64_t> *co = new Coords<int64_t>(10, 10);
    co->setX(100).setY(5);
    std::cout << *co << std::endl;
    Coords<int64_t> co1(11, 11);
    std::cout << co1 << std::endl;
    Cell< Coords<int64_t> > c(Coords<int64_t>(12,12));
    std::cout << c << std::endl;
    Cell< Coords<int64_t> > *c1 = new Cell<Coords<int64_t> >(Coords<int64_t>(13,13));
    std::cout << *c1 << std::endl;

    T_COORDS_INT_64 *tCo = new T_COORDS_INT_64(14,14);
    std::cout << *tCo << std::endl;

    T_CELL tCell(T_COORDS_INT_64(3ul, 3ul));
    std::cout << tCell << std::endl;

    T_CELL *tC = new T_CELL(T_COORDS_INT_64(15,15));
    std::cout << *tC << std::endl;

    std::cout << (tCell + c) << std::endl;
    std::cout << (*tC + *c1) << std::endl;
    std::cout << (*tC + c) << std::endl;
    std::cout << (tCell + *c1) << std::endl;

    std::cout << (tCell - c) << std::endl;
    std::cout << (*tC - *c1) << std::endl;
    std::cout << (*tC - c) << std::endl;
    std::cout << (tCell - *c1) << std::endl;

    T_COORDS_INT_64 co2(std::string(" bg56b  "));
    std::cout << co2 << std::endl;
}

#endif
