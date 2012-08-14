#ifndef __CHESS_CELL_H
#define __CHESS_CELL_H

#include <iostream>

namespace Chess {

/**
 * a single cell on a board
 * denoted by x and y co-ordinates of type T
 */
template<typename T>
class Cell {
    public:
        Cell(T &c) : coords(c) {
        }
        Cell(T *c) : coords(*c) {
        }
        Cell(T c) : coords(c) {
        }

        Cell(const Cell& c) {
            this.coords = c.coords;
        }

        Cell& operator= (const Cell& c) {
            this->coords = c.coords;

            return *this;
        }

        const Cell& operator+ (const Cell& c) {
            return new Cell(this->coords + c.coords);
        }

        const Cell& operator- (const Cell& c) {
            return new Cell(this->coords - c.coords);
        }

        const bool operator== (const Cell& c) {
            return (this.coords == c.coords);
        }

        friend std::ostream& operator<< (std::ostream& o, const Cell& c) {
            o << c.coords;
            return o;
        }
    private:
        T coords;
};

} // namespace

#endif // __CHESS_CELL_H
