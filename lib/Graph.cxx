#include "Graph.h"


#ifdef DEBUG
#include <cstdlib>

int main(int argc, char *argv[]) {
    /*
    std::vector<std::pair<int, int> > graph_vect;
    for (int i = 0; i < 100; i++) {
        graph_vect.push_back(std::pair<int, int>(rand()%20, rand()%20));
    }
    Chess::Graph<int> my_graph(graph_vect);
    */

    Chess::T_GRAPH_VECTOR gv;
    for (int i = 0; i < 10; i++) {
        gv.push_back(Chess::T_GRAPH_PAIR(Chess::T_COORDS(rand()%20+1, rand()%10), Chess::T_COORDS(rand()%2+1, rand()%15)));
    }

    Chess::T_GRAPH g(gv);

    std::cout << "End" << std::endl;

    return 0;
}
#endif // DEBUG
