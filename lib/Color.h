#ifndef __CHESS_COLOR_H
#define __CHESS_COLOR_H

namespace Chess {

class Color {
    public:
        /* Color of the piece */
        typedef enum { Black = 0, White = 1 } color;

        Color() { c = Black; }
        Color(const color& cc) {
            c = cc;
        }
        Color(const Color& cc) {
            c = cc.c;
        }

        const Color& operator= (const color &cc) {
            this->c = cc;
            return *this;
        }
        const Color& operator= (const Color &cc) {
            this->c = cc.c;
            return *this;
        }

        friend std::ostream& operator<< (std::ostream &o, const Color &col) {
            o << (int) col.c;
            return o;
        }

    private:
        color c;

};

} //namespace

#endif // __CHESS_COLOR_H
