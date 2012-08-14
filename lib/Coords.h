#ifndef __CHESS_COORDS_H
#define __CHESS_COORDS_H

#include <iostream>

namespace Chess {

/**
 * Coordinates on board
 * denoted by x and y co-ordinates of type T
 */
template<typename T>
class Coords {
    public:
        Coords(T cx, T cy) {
            x = cx;
            y = cy;
        }

        Coords(const Coords& c) {
            this->x = c.x;
            this->y = c.y;
        }

        Coords& operator= (const Coords& c) {
            this->x = c.x;
            this->y = c.y;

            return *this;
        }

        T getX() const {
            return x;
        }

        Coords& setX(T cx) {
            x = cx;
            return *this;
        }

        T getY() const {
            return y;
        }

        Coords& setY(T cy) {
            y = cy;
            return *this;
        }

        const Coords& operator+ (const Coords& c) {
            return new Coords(this.x + c.x, this.y + c.y);
        }

        const Coords& operator- (const Coords& c) {
            return new Coords(this.x - c.x, this.y - c.y);
        }

        const bool operator== (const Coords& c) {
            return (this.x == c.x && this.y == c.y);
        }

        friend std::ostream& operator<< (std::ostream& o, const Coords& c) {
            o << "X = " << c.x << std::endl
              << "Y = " << c.y;

            return o;
        }

    private:
        T x, y;
};

} // namespace

#endif // __CHESS_COORDS_H
