#include "Cell.h"

#ifdef DEBUG

#include "Coords.h"
#include <stdint.h>
#include <iostream>

using namespace Chess;

int main() {
    Coords<uint64_t> *co = new Coords<uint64_t>(10, 10);
    co->setX(100).setY(5);
    std::cout << *co << std::endl;
    Coords<uint64_t> co1(11, 11);
    std::cout << co1 << std::endl;
    Cell< Coords<uint64_t> > c(Coords<uint64_t>(12,12));
    std::cout << c << std::endl;
    Cell< Coords<uint64_t> > *c1 = new Cell<Coords<uint64_t> >(Coords<uint64_t>(13,13));
    std::cout << *c1 << std::endl;
}

#endif
