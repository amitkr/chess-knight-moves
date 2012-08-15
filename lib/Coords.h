#ifndef __CHESS_COORDS_H
#define __CHESS_COORDS_H

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>

namespace Chess {

class Exception { 
    /*
    public:
        Exception(const std::string &s) {
            std::cerr << s << std::endl;
        }
    */
};
class BadCoordsException : public Exception {
    public:
        BadCoordsException(const std::string &s) {
            std::cerr << s << std::endl;
        }
};


/**
 * Coordinates on board
 * denoted by x and y co-ordinates of type T
 */
template<typename T>
class Coords {
    public:
        Coords () { x = y = 0; }
        Coords(T cx, T cy) {
            x = cx;
            y = cy;
        }
        Coords(char *s) { }
        Coords(const std::string &s) {
            size_t start = s.find_first_not_of(" \t\n\r");
            size_t end = s.find_last_not_of(" \t\n\r");

            if (!isalpha(s[start])) {
                throw BadCoordsException("wrong co-ordinates, file cannot be numeric");
            }

            std::string str = s.substr(start, end);
            
            if (str.find_first_of(" ") != std::string::npos) {
                throw BadCoordsException("whitespace between file and rank coordinates.");
            }

            size_t split = str.find_first_of("1234567890");

            if (split <= 0) {
                throw BadCoordsException("wrong co-ordinates, rank not found");
            }

            std::string xpart = str.substr(0, split);
            std::string ypart = str.substr(split);

            x = str2num(xpart);

            errno = 0;
            y = strtoul(ypart.c_str(), NULL, 0);
            if (errno != 0) {
                throw BadCoordsException("Cannot convert rank to numeric");
            }
        }

        Coords(const Coords& c) {
            this->x = c.x;
            this->y = c.y;
        }

        ~Coords() { }

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

        Coords& operator+ (const Coords* c) {
            return *(new Coords(this->x + c->x, this->y + c->y));
        }

        Coords& operator+ (const Coords& c) {
            return *(new Coords(this->x + c.x, this->y + c.y));
        }

        Coords& operator- (const Coords* c) {
            return *(new Coords(this->x - c->x, this->y - c->y));
        }

        Coords& operator- (const Coords& c) {
            return *(new Coords(this->x - c.x, this->y - c.y));
        }

        const bool operator== (const Coords& c) {
            return (this->x == c.x && this->y == c.y);
        }

        friend std::ostream& operator<< (std::ostream& o, const Coords& c) {
            o << "X = " << c.x << std::endl
              << "Y = " << c.y << std::endl
              << "  = " << c.toString();

            return o;
        }

        std::string toString() const {
            // std::string *s = new std::string();
            std::stringstream ss(std::stringstream::in|std::stringstream::out);
            ss << num2str(x);
            ss << y;

            return ss.str();
        }

        static const T ALPHABET_SIZE = ('Z' - 'A') + 1;
    private:
        T x, y;
        T str2num(const char *s) const;
        T str2num(const std::string s) const { return str2num(s.c_str()); }
        std::string& num2str(const T n) const;
};

template<typename T>
T Coords<T>::str2num(const char *s) const {
    T w = 1, v = 0;
    while (*s) {
        v += (toupper(*s) - 'A' + 1) * w;
        w *= ALPHABET_SIZE;
        ++s;
    }
    
    return v;
}

template<typename T>
std::string& Coords<T>::num2str(const T n) const {
    std::string *s = new std::string();
    s->empty();
    T q = n;

    if (q < 0) {
        s->push_back('-');
        q = llabs(q);
    }

    while (q > ALPHABET_SIZE) {
        T r = q % ALPHABET_SIZE;
        s->push_back(char(r + 'A' - 1));
        q /= ALPHABET_SIZE;
    }
    s->push_back(char(q + 'A' - 1));

    return *s;
}


typedef Coords<uint64_t> T_COORDS_UINT_64;
typedef Coords<int64_t> T_COORDS_INT_64;

} // namespace

#endif // __CHESS_COORDS_H
