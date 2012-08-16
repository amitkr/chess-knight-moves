#ifndef __CHESS_GRAPH_H
#define __CHESS_GRAPH_H

#include <list>
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <queue>

#include <assert.h>
#include "Coords.h"

namespace Chess {
    template <typename T>
    class Graph {
        public :
            typedef std::pair<T, T> GRAPH_PAIR;
            // TODO: rename GRAPH_VECTOR to GRAPH_PAIR_VECTOR
            // maybe rename PAIR to NODE
            typedef std::vector<GRAPH_PAIR> GRAPH_VECTOR;
            typedef std::queue<GRAPH_PAIR> GRAPH_PAIR_QUEUE;

            explicit Graph(const GRAPH_VECTOR &v);
            Graph() { }

            ~Graph() {}

            void setVertex(T k1, T k2, long w = 1);

            std::vector<T> bfs(T from, T to);
            std::vector<T> dijkstra(T from, T to);

            friend std::ostream& operator<< (std::ostream &o, const Graph<T> &g) {
                o << "G{" << std::endl;
                for (typename std::list<Vertex>::const_iterator it = g.vertices.begin(); it != g.vertices.end(); ++it) {
                    o << *it << ", " << std::endl;
                }
                o << "}";
            }

            typedef enum { Visited = 1, NotVisited = 0 } Visits;

        private:
            class Vertex;

            struct Edge {
              Edge(Vertex *e, long w) : edge(e), weight(w) {}
              Vertex *edge;
              long weight;
              friend std::ostream& operator<< (std::ostream& o, const Edge &e) {
                  o << "E(" << e.edge->getKey() << ", " << e.weight << ")";
                  // o << e.edge->getKey();
                  return o;
              }
            };

            class Vertex {
                public:
                  Vertex(T k) : key(k), visit(NotVisited), cost(0.0) {}
                  void setEdge(Vertex *adjacent, long w = 1);
                  const T getKey() const {
                      return key;
                  }
                  const std::list<Edge> &getEdges() const {
                      return edges;
                  }
                  double getCost() const {
                      return cost;
                  }
                  double setCost(double c) {
                      cost += c;
                  }
                  void setVisited() {
                      visit = Visited;
                  }
                  bool isVisited() const {
                      return (visit == Visited);
                  }
                  void setNotVisited() {
                      visit = NotVisited;
                  }
                  bool isNotVisited() const {
                      return (visit == NotVisited);
                  }
                  friend std::ostream& operator<< (std::ostream &o, const Vertex &v) {
                      o << "V[" << v.getKey() << " -> ";
                      for (typename std::list<Edge>::const_iterator it = v.edges.begin(); it != v.edges.end(); ++it) {
                          o << *it << ", ";
                      }
                      o << "]";
                  }
                private:
                  std::list<Edge> edges;
                  T key;
                  Visits visit;
                  double cost;
                  bool hasEdge(const T key);
            };

            struct compare {
                bool operator()(const Vertex *lhs, const Vertex *rhs) const {
                    return lhs->getCost() < rhs->getCost();
                }
            };

            std::list<Vertex> vertices;
            Vertex *hasVertex(const T key);
    };

    // typedef std::pair<T_COORDS, T_COORDS> T_GRAPH_PAIR;
    // typedef std::vector<T_GRAPH_PAIR> T_GRAPH_VECTOR;
    typedef Graph<T_COORDS> T_GRAPH;
    typedef T_GRAPH::GRAPH_PAIR T_GRAPH_PAIR;
    typedef T_GRAPH::GRAPH_VECTOR T_GRAPH_VECTOR;


    template <typename T>
    std::vector<T> Graph<T>::bfs(T from, T to) {
        std::vector<T> path;

        Vertex *v = hasVertex(from);
        if (!v) return path;
        Vertex *t = hasVertex(to);
        if (!t) return path;

        std::queue<Vertex*> q;

        v->setVisited();
        q.push(v);

        while (!q.empty()) {
            Vertex *c = q.front();
            q.pop();

            if (!c) {
                return path;
            }
            if (c->getKey() == to) {
                return path;
            }

            std::list<Edge> e = c->getEdges();

            for (typename std::list<Edge>::const_iterator it = e.begin(); it != e.end(); ++it) {
                Vertex *o = it->edge;

                if (o->isVisited()) {
                    continue;
                }

                if (!o) {
                    return path;
                }
                if (o->getKey() == to) {
                    return path;
                }

                o->setVisited();
                q.push(o);
            }
            path.push_back(c->getKey());
        }
        return path;
    }

    template <typename T>
    std::vector<T> Graph<T>::dijkstra(T from, T to) {
        std::vector<T> path;

        path.push_back(from);

        Vertex *f = hasVertex(from);
        if (!f) return path;
        Vertex *t = hasVertex(to);
        if (!t) return path;

        std::priority_queue<Vertex*, std::deque<Vertex*>, compare> pq;
        pq.push(f);

        while(!pq.empty()) {
            Vertex *c = pq.top();
            pq.pop();

            if (!c) { return path; }
            if (c->getKey() == to) { return path; }

            std::list<Edge> e = c->getEdges();
            for(typename std::list<Edge>::const_iterator it = e.begin(); it != e.end(); ++it) {
                Vertex *o = it->edge;
                if (o->isVisited()) { continue; }
                o->setCost(o->getCost() + it->weight);
                o->setVisited();
                pq.push(o);
                path.push_back(o->getKey());
            }
        }

        return path;
    }
}

template <typename T>
Chess::Graph<T>::Graph (const GRAPH_VECTOR &v) {
    typename GRAPH_VECTOR::const_iterator it = v.begin ();

    for (; it != v.end (); ++it) {
        setVertex (it->first, it->second);
    }
}

template <typename T>
void Chess::Graph<T>::setVertex(T k1, T k2, long w) {
    Chess::Graph<T>::Vertex * v1 = hasVertex(k1);
    Chess::Graph<T>::Vertex * v2 = hasVertex(k2);

    if (v1 == NULL) {
        vertices.push_back(Vertex(k1));
        v1 = hasVertex(k1);
    }
    if (v2 == NULL) {
        vertices.push_back(Vertex(k2));
        v2 = hasVertex(k2);
    }

    assert(v1 != NULL);
    assert(v2 != NULL);

    if (v1 != NULL && v2 != NULL) {
        v1->setEdge(v2, w);
        v2->setEdge(v1, w);
    } else {
        throw std::runtime_error ("Unknown");
    }
}

template <typename T>
typename Chess::Graph<T>::Vertex* Chess::Graph<T>::hasVertex(T key) {
    typename std::list<Vertex>::iterator find_it = vertices.begin();

    for (; find_it != vertices.end(); ++find_it) {
        if (find_it->getKey() == key) {
            return &(*find_it);
        }
    }

    return NULL;
}

template <typename T>
void Chess::Graph<T>::Vertex::setEdge (Chess::Graph<T>::Vertex *adjacent, long w) {
    if (adjacent == NULL)
        return;

    if (!hasEdge(adjacent->getKey())) {
        Chess::Graph<T>::Edge e(adjacent, w);
        edges.push_back(e);
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
