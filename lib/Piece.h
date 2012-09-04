#ifndef __CHESS_PIECE_H
#define __CHESS_PIECE_H

#include <vector>
#include <list>
#include <queue>

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
        virtual std::list<T_COORDS> findPath(T_COORDS &to) = 0;
        virtual std::list<T_COORDS> findPath(T_COORDS &from, T_COORDS &to) = 0;
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

        virtual std::list<T_COORDS> findPath(T_COORDS &from, T_COORDS &to) {
            std::list<T_COORDS> r;
            return r;
        }

        // prepare the graph
        void findPaths(T_COORDS &from, T_COORDS &to) {
            ++depth;
            // gv.push_back(Chess::T_GRAPH_PAIR(T_COORDS(0, 0), from));
            //
            // a. create the possible moves from "from"
            // b. push these into a queue and graph vector
            // c. check if we've already found the destination "to"
            // d. pop each move from the queue and repeat from a.
            //
            if (!found && depth < MAX_SEARCH_DEPTH)
            for (K_MOVES::iterator it = moves.begin(); it != moves.end(); ++it) {
                T_COORDS next = from + *it;
                // TODO: these limits should be enforced by Board class which
                // is yet to be implemented
                // if (next < 1 || next > 8) continue;
                cq.push(next);
                // gv.push_back(Chess::T_GRAPH_PAIR(from, next));
                // g.setVertex(from, next, depth);
                g.setVertex(from, next, depth);

                if (to == next) {
                    found = true;
                }
            }

            while (!cq.empty()) {
                T_COORDS e = cq.front();
                cq.pop();
                findPaths(e, to);
            }
        }

        virtual std::list<T_COORDS> findPath(T_COORDS &to) {
            found = false;
            depth = 0;

            findPaths(pos, to);

#ifdef DEBUG
            std::cout << g << std::endl;
#endif

            /*
            std::vector<T_COORDS> path = g.bfs(pos, to);
            for (std::vector<T_COORDS>::const_iterator it = path.begin();
                    it != path.end(); ++it) {
                std::cout << *it << ", ";
            }
            std::cout << std::endl;
            */

            return g.dijkstra(pos, to);
        }

        K_MOVES getMoves() const {
            return moves;
        }

        friend std::ostream& operator<< (std::ostream &o, const Knight &k) {
            o << "N [" << k.pos << ", " << k.color << "]" << std::endl;
            return o;
        }

    private:
        // T_GRAPH_VECTOR gv;
        T_COORDS_QUEUE cq;
        // T_COORDS_VECTOR path;
        bool found;
        unsigned int depth;
        static const unsigned int MAX_SEARCH_DEPTH = 10000;
        T_GRAPH g;


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
