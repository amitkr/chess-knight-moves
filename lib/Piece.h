#ifndef __CHESS_PIECE_H
#define __CHESS_PIECE_H

#include <vector>
#include <list>

#include "Cell.h"
#include "Color.h"
#include "Graph.h"

namespace Chess {

class Piece {
    protected:
        Color color;
        T_COORDS pos;

    public:
        virtual ~Piece() { }
        // virtual T_COORDS& findNextMove(T_COORDS &from, T_COORDS &to) = 0;
        virtual std::vector<T_COORDS> findPath(T_COORDS &to) = 0;
        virtual std::vector<T_COORDS> findPath(T_COORDS &from, T_COORDS &to) = 0;
};

// King
// Rook
// Bishop
// Queen

/**
 */
class Knight : public Piece {
    public:
        typedef std::list<T_COORDS> K_MOVES;

        Knight() {
            pos = T_COORDS(std::string("a1"));
            color = Color::Black;
            // pos = T_COORDS("d3");
            setMoves();

        }
        Knight(T_COORDS c, Color col = Color(Color::Black)) {
            pos = c;
            color = col;
            setMoves();
        }
        Knight(T_COORDS &c, Color col = Color(Color::Black)) {
            pos = c;
            color = col;
            setMoves();
        }
        Knight(std::string &s, Color col = Color(Color::Black)) {
            pos = s;
            color = col;
            setMoves();
        }
        Knight(Knight &k) {
            pos = k.pos;
            color = k.color;
            setMoves();
        }
        ~Knight() { }

        // find the shortest path
        virtual std::vector<T_COORDS> findPath(T_COORDS &from, T_COORDS &to) {
        }

        virtual std::vector<T_COORDS> findPath(T_COORDS &to) {
            T_GRAPH_VECTOR gv;
            gv.push_back(Chess::T_GRAPH_PAIR(T_COORDS(0, 0), pos));
            for (K_MOVES::iterator it = moves.begin(); it != moves.end(); ++it) {
                gv.push_back(Chess::T_GRAPH_PAIR(pos, (pos + *it)));
            }

            T_GRAPH g(gv);

            std::vector<T_COORDS> vec;
            vec.push_back(pos);

            return vec;
        }

        K_MOVES getMoves() const {
            return moves;
        }

        friend std::ostream& operator<< (std::ostream &o, const Knight &k) {
            o << "N [" << k.pos << ", " << k.color << "]" << std::endl;
            return o;
        }

    private:
        K_MOVES moves;
        void setMoves() {
            moves.push_back(T_COORDS( 1,  2));
            moves.push_back(T_COORDS( 2,  1));
            moves.push_back(T_COORDS( 2, -1));
            moves.push_back(T_COORDS( 1, -2));
            moves.push_back(T_COORDS(-1, -2));
            moves.push_back(T_COORDS(-2, -1));
            moves.push_back(T_COORDS(-2,  1));
            moves.push_back(T_COORDS(-1,  2));

#ifdef DEBUG
            // if (!pos) pos = T_COORDS(std::string("d3"));
            std::cout << "Pos = " << pos << std::endl;
            for (std::list<T_COORDS>::iterator it = moves.begin(); it != moves.end(); ++it)
                std::cout << (pos + *it) << std::endl;
#endif
        }

};


// Pawn


} //namespace

#endif // __CHESS_PIECE_H
