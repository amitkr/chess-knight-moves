#ifndef __CHESS_GRAPH_H
#define __CHESS_GRAPH_H

#include <list>
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <assert.h>

#include "Coords.h"

namespace Chess {
    template <typename T>
    class Graph {
        public :
            typedef std::pair<T, T> GRAPH_PAIR;
            typedef std::vector<GRAPH_PAIR> GRAPH_VECTOR;

            explicit Graph(const GRAPH_VECTOR &v);

            ~Graph() {}
            void setVertex(T k1, T k2);

        private:
            class Vertex;

            struct Edge {
              Edge(Vertex *e, long w) : edge(e), weight(w) {}
              Vertex *edge;
              long weight;
            };

            class Vertex {
                public:
                  Vertex(T k) : key(k) {}
                  void setEdge(Vertex *adjacent);
                  const T getKey() const {return key;}
                  const std::list<Edge> &getEdges() const {return edges;}
                private:
                  std::list<Edge> edges;
                  T key;
                  bool hasEdge(const T key);
            };

            std::list<Vertex> vertices;
            Vertex *hasVertex(const T key);
    };

    // typedef std::pair<T_COORDS, T_COORDS> T_GRAPH_PAIR;
    // typedef std::vector<T_GRAPH_PAIR> T_GRAPH_VECTOR;
    typedef Graph<T_COORDS> T_GRAPH;
    typedef T_GRAPH::GRAPH_PAIR T_GRAPH_PAIR;
    typedef T_GRAPH::GRAPH_VECTOR T_GRAPH_VECTOR;
}

template <typename T>
Chess::Graph<T>::Graph (const GRAPH_VECTOR &v) {
#ifdef DEBUG
    std::cout <<"Inserting pairs: " << std::endl;
#endif
    typename GRAPH_VECTOR::const_iterator insert_it = v.begin ();

    for (; insert_it != v.end (); ++insert_it) {
#ifdef DEBUG
        std::cout << insert_it->first << " --> " << insert_it->second << std::endl;
#endif
        setVertex (insert_it->first, insert_it->second);
    }
#ifdef DEBUG
    std::cout << "Printing results: " << std::endl;
    typename std::list<Vertex>::iterator print_it = vertices.begin(); 
    for (; print_it != vertices.end(); ++print_it) {
        std::cout << print_it->getKey();
        typename std::list<Edge>::const_iterator edge_it = print_it->getEdges().begin(); 
        for (; edge_it != print_it->getEdges().end(); ++edge_it) {
            std::cout << "-->" << edge_it->edge->getKey();
        }
        std::cout << std::endl;
    }
#endif
}

template <typename T>
void Chess::Graph<T>::setVertex(T k1, T k2) {
    Chess::Graph<T>::Vertex * v1 = hasVertex (k1);
    Chess::Graph<T>::Vertex * v2 = hasVertex (k2);

    if (v1 == NULL) {
        vertices.push_back (Vertex(k1));
        v1 = hasVertex (k1);
    }
    if (v2 == NULL) {
        vertices.push_back (Vertex(k2));
        v2 = hasVertex (k2);
    }

    assert (v1 != NULL);
    assert (v2 != NULL);

    if (v1 != NULL && v2 != NULL) {
        v1->setEdge (v2);
        v2->setEdge (v1);
    } else {
        throw std::runtime_error ("Unknown");
    }
}

template <typename T>
typename Chess::Graph<T>::Vertex* Chess::Graph<T>::hasVertex (T key) {
    typename std::list<Vertex>::iterator find_it = vertices.begin ();

    for (; find_it != vertices.end (); ++find_it) {
        if (find_it->getKey () == key) {
            return &(*find_it);
        }
    }

    return NULL;
}

template <typename T>
void Chess::Graph<T>::Vertex::setEdge (Chess::Graph <T>::Vertex * adjacent) {
    if (adjacent == NULL)
        return;

    if (!hasEdge (adjacent->getKey ())) {
        Chess::Graph <T>::Edge e (adjacent, 1);
        edges.push_back (e);
    }
}

template <typename T>
bool Chess::Graph<T>::Vertex::hasEdge (const T key) {
    typename std::list<Edge>::iterator find_it = edges.begin ();

    for (; find_it != edges.end (); ++find_it) {
        if (find_it->edge->getKey () == key) {
            return true;
        }
    }
    return false;
}

#endif // __CHESS_GRAPH_H
