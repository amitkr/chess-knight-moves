#ifndef __CHESS_BOARD_H
#define __CHESS_BOARD_H

#include <stdint.h>
#include <vector>

#include "Cell.h"

namespace Chess {

template <typename T>
class Board {
    public:
        Board() : xlen(0), ylen(0) { }
        Board(T cx, T cy) : xlen(cx), ylen(cy) { }

        Board(const Board& b) {
            this->xlen = b.xlen;
            this->ylen = b.xlen;
        }

        Board& operator= (const Board& b) {
            this->xlen = b.xlen;
            this->ylen = b.ylen;

            return *this;
        }

        T getX() const {
            return xlen;
        }

        T getY() const {
            return ylen;
        }

    private:
        T xlen, ylen;
        std::vector< Cell<T> > c;
};

typedef Board<uint64_t> CHESS_BOARD;

} // namespace

#endif // __CHESS_BOARD_H
