#ifndef __CHESS_GRAPH_H
#define __CHESS_GRAPH_H

#include <list>
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <queue>
#include <set>
#include <map>
#include <limits>
#include <utility>

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
            typedef double Weight;
            typedef long Cost;

            explicit Graph(const GRAPH_VECTOR &v);
            Graph() { }
            ~Graph() {}

            void setVertex(T k1, T k2, Weight w = 1);

            std::vector<T> bfs(T from, T to);
            std::vector<T> dijkstra(T from, T to);

            friend std::ostream& operator<< (std::ostream &o, const Graph<T> &g) {
                o << "G{" << std::endl;
                for (typename std::list<Vertex>::const_iterator it = g.vertices.begin();
                        it != g.vertices.end();
                        ++it)
                {
                    o << *it << ", " << std::endl;
                }
                o << "}";

                return o;
            }

            typedef enum { Visited = 1, NotVisited = 0 } Visits;

        private:
            class Vertex;

            struct Edge {
              Edge(Vertex *e, Weight w) : edge(e), weight(w) {}
              Vertex *edge;
              Weight weight;
              friend std::ostream& operator<< (std::ostream& o, const Edge &e) {
                  o << "E(" << e.edge->getKey() << ", " << e.weight << ")";
                  // o << e.edge->getKey();
                  return o;
              }
            };

            class Vertex {
                public:
                    Vertex() : visit(NotVisited), cost(1) { };
                    Vertex(T k) : key(k), visit(NotVisited), cost(1) {}
                    Vertex(const Vertex &v) {
                        key = v.key;
                        visit = v.visit;
                        cost = v.cost;
                        edges = v.edges;
                    }
                    const Vertex& operator=(const Vertex &v) {
                        key = v.key;
                        visit = v.visit;
                        cost = v.cost;
                        edges = v.edges;
                        return *this;
                    }
                    void setEdge(Vertex *adjacent, Weight w = 1);
                    const T getKey() const {
                        return key;
                    }
                    const std::list<Edge> &getEdges() const {
                        return edges;
                    }
                    Cost getCost() const {
                        return cost;
                    }
                    Cost setCost(Cost c) {
                        return cost += c;
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
                        for (typename std::list<Edge>::const_iterator it = v.edges.begin();
                                it != v.edges.end();
                                ++it)
                        {
                            o << *it << ", ";
                        }
                        o << "]";

                        return o;
                    }
                private:
                    std::list<Edge> edges;
                    T key;
                    Visits visit;
                    Cost cost;
                    bool hasEdge(const T key);
            };

            struct compare {
                bool operator()(const Vertex &lhs, const Vertex &rhs) const {
                    return lhs.getCost() < rhs.getCost();
                }
                bool operator()(const Vertex *lhs, const Vertex *rhs) const {
                    return lhs->getCost() < rhs->getCost();
                }
                bool operator()(const Vertex &lhs, const Weight &w) const {
                    // ERROR!
                    return lhs.getCost() < w;
                }
                bool operator()(const Weight &w, const Vertex &rhs) const {
                    // ERROR!
                    return w < rhs.getCost();
                }
                bool operator()(const std::pair<Weight, Vertex> &lhs,
                        const std::pair<Weight, Vertex> &rhs) const
                {
                    return lhs.first < rhs.first;
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


    /**
     *
     */
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

            for (typename std::list<Edge>::const_iterator it = e.begin();
                    it != e.end();
                    ++it)
            {
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

    /**
     *
     */
    template <typename T>
    std::vector<T> Graph<T>::dijkstra(T from, T to) {
        std::vector<T> path;
        path.push_back(from);

        Vertex *f = hasVertex(from);
        std::cout << "From: " << *f << std::endl;
        if (!f) return path;
        Vertex *t = hasVertex(to);
        if (!t) return path;

        typedef std::map<Vertex, Weight, compare> DISTANCE_T;
        typedef std::map<Vertex, Vertex, compare> MAP_T;

        DISTANCE_T minDistance;
        MAP_T prev;

        // std::cout << "Infinity = " << std::numeric_limits<double>::infinity() << std::endl;
        // std::cout << "Infinity = " << std::numeric_limits<Weight>::infinity() << std::endl;

        for (typename std::list<Vertex>::const_iterator it = vertices.begin();
                it != vertices.end();
                ++it)
        {
            Vertex v = *it;
            minDistance[v] = std::numeric_limits<Weight>::infinity();
            /*
            std::cout << "v = " << v
                << " minDistance = " << minDistance[v]
                << std::endl;
            */

            std::list<Edge> e = it->getEdges();
            for (typename std::list<Edge>::const_iterator eit = e.begin();
                    eit != e.end();
                    ++eit)
            {
                Vertex *v2 = eit->edge;
                minDistance[*v2] = std::numeric_limits<Weight>::infinity();
                /*
                std::cout << "v2 = " << *v2
                    << " minDistance = " << minDistance[*v2]
                    << std::endl;
                */
            }
            std::cout << "minDistance has " << minDistance.size() << " elements."
                << std::endl;
        }

        std::cout << "minDistance has " << minDistance.size() << " elements."
            << std::endl;

        minDistance[*f] = 0;

        std::cout << "v = " << *t
            << " minDistance = " << minDistance[*t]
            << std::endl;

        std::cout << "v = " << *f
            << " minDistance = " << minDistance[*f]
            << std::endl;


        std::set<std::pair<Weight, Vertex>, compare> vq;
        vq.insert(std::make_pair(minDistance[*f], *f));

        while(!vq.empty()) {
            Vertex c = vq.begin()->second;
            vq.erase(vq.begin());

            std::cout << "Processing: " << c << std::endl;

            const std::list<Edge> &el = c.getEdges();
            for(typename std::list<Edge>::const_iterator it = el.begin();
                    it != el.end();
                    ++it)
            {
                Vertex v = *(it->edge);
                Weight w = it->weight;
                Weight dvc = minDistance[c] + w; // distance via c
                std::cout << "Subprocessing: " << v
                    << " w = " << w
                    << " dvc = " << dvc
                    << " minDistance[v] = " << minDistance[v] << std::endl;
                if (dvc < minDistance[v]) {
                    vq.erase(std::make_pair(minDistance[v], v));
                    minDistance[v] = dvc;
                    prev[v] = c;
                    vq.insert(std::make_pair(minDistance[v], v));
                }
            }
        }

        for (typename MAP_T::const_iterator it = prev.begin();
                it != prev.end();
                ++it)
        {
            std::cout
                << "(" << it->first.getKey()
                << ", " << it->second.getKey()
                << ")" << std::endl;
        }

        Vertex start = *t;
        typename MAP_T::const_iterator it_prev;
        while((it_prev = prev.find(start)) != prev.end()) {
            start = prev[start];
            path.push_back(start.getKey());
        }

        return path;
    }

} // namespace

template <typename T>
Chess::Graph<T>::Graph (const GRAPH_VECTOR &v) {
    for (typename GRAPH_VECTOR::const_iterator it = v.begin ();
            it != v.end();
            ++it)
    {
        setVertex(it->first, it->second);
    }
}

template <typename T>
void Chess::Graph<T>::setVertex(T k1, T k2, Weight w) {
    Chess::Graph<T>::Vertex *v1 = hasVertex(k1);
    Chess::Graph<T>::Vertex *v2 = hasVertex(k2);

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
void Chess::Graph<T>::Vertex::setEdge (Chess::Graph<T>::Vertex *adjacent, Weight w) {
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
