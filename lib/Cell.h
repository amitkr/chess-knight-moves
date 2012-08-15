#ifndef __CHESS_CELL_H
#define __CHESS_CELL_H

#include <iostream>
#include <stdint.h>
#include "Coords.h"

namespace Chess {

/**
 * a single cell on a board
 * denoted by x and y co-ordinates of type T
 */
template<typename T>
class Cell {
    public:
        Cell() { }
        Cell(T c) : coords(c) { }

        Cell(const Cell& c) {
            this->coords = c.coords;
        }

        Cell& operator= (const Cell& c) {
            this->coords = c.coords;

            return *this;
        }

        ~Cell() { }

        const Cell& operator+ (const Cell *c) {
            return *(new Cell(this->coords + c->coords));
        }

        const Cell& operator+ (const Cell& c) {
            return *(new Cell(this->coords + c.coords));
        }

        const Cell& operator- (const Cell* c) {
            return *(new Cell(this->coords - c->coords));
        }

        const Cell& operator- (const Cell& c) {
            return *(new Cell(this->coords - c.coords));
        }

        const bool operator== (const Cell& c) {
            return (this->coords == c.coords);
        }

        friend std::ostream& operator<< (std::ostream& o, const Cell& c) {
            o << c.coords;
            return o;
        }
    private:
        T coords;
};

typedef Cell<T_COORDS_UINT_64> T_CELL_UINT_64;
typedef Cell<T_COORDS_INT_64> T_CELL;

} // namespace

#endif // __CHESS_CELL_H
